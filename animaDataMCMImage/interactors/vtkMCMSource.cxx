#include <vector>
#include <complex>
#include <cmath>

#include <vtkMCMSource.h>

#include <vtkPolyDataNormals.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkMath.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkMatrix4x4.h>
#include <vtkStreamingDemandDrivenPipeline.h>

#include <animaDDIDistribution.h>

vtkStandardNewMacro(vtkMCMSource);

vtkMCMSource::vtkMCMSource(const int tess)
{
    Radius = 1.0e-3;
    Center[0] = 0.0;
    Center[1] = 0.0;
    Center[2] = 0.0;

    RotationMatrix = 0;
    InverseRotationMatrix = vtkMatrix4x4::New();
    InverseRotationMatrix->Identity();

    Normalization = false;

    SetNumberOfInputPorts(0);

    // By Default we flip the z-axis, the internal x,y,z have z flipped with respect to visu
    SetFlipVector(false,false,false);

    TesselationType = Icosahedron;
    Tesselation = tess;

    sphereT = vtkTessellatedSphereSource::New();
    sphereT->SetResolution(Tesselation);

    MCMData.SetSize(0);
}

vtkMCMSource::~vtkMCMSource()
{
    if (sphereT)
        sphereT->Delete();

    if(RotationMatrix)
        RotationMatrix->Delete();
}

void vtkMCMSource::SetRotationMatrix(vtkMatrix4x4 *mat)
{
    if (!mat)
        return;

    vtkSetObjectBodyMacro(RotationMatrix, vtkMatrix4x4, mat);

    vtkMatrix4x4::Invert(this->RotationMatrix, this->InverseRotationMatrix);
}

int *vtkMCMSource::GetTesselationRange()
{
    int* range = new int[2];
    GetTesselationRange(range);
    return range;
}

void vtkMCMSource::GetTesselationRange(int *range)
{
    range[0] = 2;
    range[1] = 5;
}

int vtkMCMSource::RequestData(vtkInformation *vtkNotUsed(request),vtkInformationVector **vtkNotUsed(inputVector),
                              vtkInformationVector *outputVector)
{
    // Get the info and output objects.
    vtkInformation *outInfo = outputVector->GetInformationObject(0);
    vtkPolyData *output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));
    const unsigned int N = sphereT->GetOutput()->GetNumberOfPoints();

    vtkFloatArray* sValues = vtkFloatArray::New();
    sValues->SetNumberOfTuples(N);
    sValues->SetNumberOfComponents(1);

    referenceMCM->SetModelVector(MCMData);
    double sumWeightsMCM = 0;
    for (unsigned int i = 0;i < referenceMCM->GetNumberOfCompartments();++i)
        sumWeightsMCM += referenceMCM->GetCompartmentWeight(i);

    if (sumWeightsMCM == 0)
    {
        for (unsigned int i=0;i < N;++i)
            sValues->SetTuple1(i,0);

        sphereT->GetOutput()->GetPointData()->SetScalars(sValues);
        sValues->Delete();

        // Don't know how to copy everything but the points.
        output->DeepCopy(sphereT->GetOutput());
        output->GetPoints()->Reset();

        TranslateAndDeformShell(sphereT->GetOutput(),output->GetPoints(),Center,RotationMatrix);

        return 1;
    }

    vtkPoints* vertices = sphereT->GetOutput()->GetPoints();
    vnl_vector_fixed <double,3> point;

    double maxSValue = 0;
    double minSValue = VTK_DOUBLE_MAX;

    for (unsigned int i=0;i < N;++i)
    {
        double p[4];
        vertices->GetPoint(i,p);
        p[3] = 1.0;

        if (InverseRotationMatrix)
        {
            const double *pTmp = InverseRotationMatrix->MultiplyDoublePoint(p);
            for (unsigned int j = 0;j < 3;++j)
                p[j] = pTmp[j];
        }

        for (unsigned int j = 0;j < 3;++j)
            point[j] = (FlipVector[j]) ? -p[j] : p[j];

        point *= Radius;

        double sValue = referenceMCM->GetDiffusionProfile(point);

        if (i % 10000 == 0)
        {
            UpdateProgress ((float)i/N);
            if (GetAbortExecute())
                break;
        }

        if (sValue > maxSValue)
            maxSValue = sValue;
        if (sValue < minSValue)
            minSValue = sValue;

        sValues->SetTuple1(i,sValue);
    }

    if (maxSValue != minSValue)
    {
        for (unsigned int i=0;i < N;++i)
        {
            if (Normalization)
            {
                double normalizedValue = (sValues->GetTuple1(i) - minSValue) / (maxSValue - minSValue);
                sValues->SetTuple1(i,normalizedValue);
            }
            else
            {
                double normalizedValue = sValues->GetTuple1(i) / 1000;
                sValues->SetTuple1(i,normalizedValue);
            }
        }
    }
    else
    {
        for (unsigned int i=0;i < N;++i)
            sValues->SetTuple1(i,1.0);
    }

    sphereT->GetOutput()->GetPointData()->SetScalars(sValues);
    sValues->Delete();

    // Don't know how to copy everything but the points.
    output->DeepCopy(sphereT->GetOutput());
    output->GetPoints()->Reset();

    TranslateAndDeformShell(sphereT->GetOutput(),output->GetPoints(),Center,RotationMatrix);

    return 1;
}

void vtkMCMSource::PrintSelf(ostream& os,vtkIndent indent)
{
    Superclass::PrintSelf(os,indent);

    os << indent << "Tessellation Order: " << Tesselation << std::endl;
    os << indent << "Tessellation Type: " << TesselationType << std::endl;
    os << indent << "Radius: " << Radius << std::endl;
}

int vtkMCMSource::RequestInformation(vtkInformation*,vtkInformationVector**,vtkInformationVector *outputVector)
{
    // Get the info object
    vtkInformation* outInfo = outputVector->GetInformationObject(0);

    outInfo->Set(CAN_HANDLE_PIECE_REQUEST(), 1);

    return 1;
}

void vtkMCMSource::SetMCMData(MCModelVectorType &_arg)
{
    MCMData = _arg;
    Modified();
}

void vtkMCMSource::UpdateMCMSource()
{
    sphereT->SetPolyhedraType(TesselationType);
    sphereT->SetResolution(Tesselation);
    sphereT->Update();

    Modified();
}

void vtkMCMSource::TranslateAndDeformShell(vtkPolyData *shell,vtkPoints* outPts,double center[3],
                                           vtkMatrix4x4* transform)
{
    vtkPoints* inPts = shell->GetPoints();
    const int n = inPts->GetNumberOfPoints();

    vtkDataArray* sValues = shell->GetPointData()->GetScalars();

    double point[4];
    point[3] = 1;
    for (int i=0;i<n;++i)
    {
        inPts->GetPoint(i,point);

        const double val = sValues->GetTuple1(i);
        point[0] = val*point[0];
        point[1] = val*point[1];
        point[2] = val*point[2];

        const double* pointOut = (transform!=0) ? transform->MultiplyDoublePoint(point) : &point[0];
        outPts->InsertNextPoint(pointOut[0]+center[0],pointOut[1]+center[1],pointOut[2]+center[2]);
    }
}
