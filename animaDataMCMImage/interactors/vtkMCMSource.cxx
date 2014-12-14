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

vtkCxxRevisionMacro(vtkMCMSource,"$Revision: 0 $");
vtkStandardNewMacro(vtkMCMSource);

vtkMCMSource::vtkMCMSource(const int tess)
{
    Radius = 1.0e-3;
    Center[0] = 0.0;
    Center[1] = 0.0;
    Center[2] = 0.0;
    RotationMatrix = 0;
    Normalization = false;

    SetNumberOfInputPorts(0);

    // By Default we flip the z-axis, the internal x,y,z have z flipped with respect to visu
    SetFlipVector(false,false,false);

    TesselationType = Icosahedron;
    Tesselation = tess;

    sphereT = vtkTessellatedSphereSource::New();
    sphereT->SetResolution(Tesselation);

    MCMData = 0;
    NumberOfCompartments = 0;
}

vtkMCMSource::~vtkMCMSource()
{
    if (sphereT)
        sphereT->Delete();

    if(RotationMatrix)
        RotationMatrix->Delete();

    // TO DO : check this is not causing crashes
    if (MCMData)
        delete[] MCMData;

    MCMData = 0;
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

    if (!MCMData)
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

    vtkMatrix4x4 *InverseRotationMatrix = 0;
    if (RotationMatrix)
    {
        InverseRotationMatrix = vtkMatrix4x4::New();
        vtkMatrix4x4::Invert(RotationMatrix,InverseRotationMatrix);
    }

    vtkPoints* vertices = sphereT->GetOutput()->GetPoints();
    vnl_vector_fixed <double,3> point;

    unsigned int dataSize = NumberOfCompartments * anima::CompartmentSize + 4;
    std::vector <double> dataMCM(dataSize,0);

    double maxSValue = 0;
    double minSValue = VTK_DOUBLE_MAX;

    for (unsigned int i=0;i < N;++i)
    {
        double p[4];
        vertices->GetPoint(i,p);
        p[3] = 1.0;

        if (InverseRotationMatrix)
            InverseRotationMatrix->MultiplyDoublePoint(p);

        for (unsigned int j = 0;j < 3;++j)
            point[j] = (FlipVector[j]) ? -p[j] : p[j];

        point *= Radius;

        for (unsigned int j = 0;j < dataSize;++j)
            dataMCM[j] = MCMData[j];

        double sValue = anima::ComputeDDIPdf(point, dataMCM);

        if (i % 10000 == 0)
        {
            UpdateProgress ((vtkFloatingPointType)i/N);
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
                double normalizedValue = sValues->GetTuple1(i) / 10000;
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

    outInfo->Set(vtkStreamingDemandDrivenPipeline::MAXIMUM_NUMBER_OF_PIECES(),-1);
    outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_BOUNDING_BOX(),
                 Center[0]-1,Center[0]+1,
            Center[1]-1,Center[1]+1,
            Center[2]-1,Center[2]+1);

    return 1;
}

void vtkMCMSource::SetMCMData(double *_arg, unsigned int size)
{
    MCMData = _arg;
    NumberOfCompartments = (size - 4) / anima::CompartmentSize;

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
    const int  n = inPts->GetNumberOfPoints();

    vtkDataArray* sValues  = shell->GetPointData()->GetScalars();

    for (int i=0;i<n;++i)
    {
        double point[4];
        inPts->GetPoint(i,point);

        const double val = sValues->GetTuple1(i);
        point[0] = val*point[0];
        point[1] = val*point[1];
        point[2] = val*point[2];

        point[3] = 1.0;
        const double* pointOut = (transform!=0) ? transform->MultiplyDoublePoint(point) : &point[0];
        outPts->InsertNextPoint(pointOut[0]+center[0],pointOut[1]+center[1],pointOut[2]+center[2]);
    }
}
