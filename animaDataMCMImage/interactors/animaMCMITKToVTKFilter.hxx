#include <vtkPointData.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkFloatArray.h>

#include <itkImage.h>
#include <itkImageToImageFilter.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIteratorWithIndex.h>

#include <vtkMCMGlyph.h>

template < class TMCMImage >
animaMCMITKToVTKFilter< TMCMImage >
::animaMCMITKToVTKFilter()
{
    m_VTKMCMData = vtkImageData::New();
    m_DirectionMatrix = vtkMatrix4x4::New();
    m_DirectionMatrix->Identity();
}

template < class TMCMImage >
animaMCMITKToVTKFilter< TMCMImage >
::~animaMCMITKToVTKFilter()
{
    m_VTKMCMData->Delete();
    m_DirectionMatrix->Delete();
}

template < class TMCMImage >
void
animaMCMITKToVTKFilter< TMCMImage >
::CopyVTKSphericalHarmonic( vtkImageData* p )
{
    p->DeepCopy(m_VTKMCMData);
}

template < class TMCMImage >
typename animaMCMITKToVTKFilter<TMCMImage>::MCMImageType*
animaMCMITKToVTKFilter< TMCMImage >
::GetOutput()
{
    return const_cast<TMCMImage*>( this->GetInput() );
}

template < class TMCMImage >
void
animaMCMITKToVTKFilter<TMCMImage>::GenerateData()
{
    MCMImageConstPointer inputMCM = this->GetInput(0);
    if (!inputMCM)
        throw itk::ExceptionObject (__FILE__,__LINE__,"Error: No input ITK MCM image has been set.");

    // conversion itkVectorImage -> vtkImageData
    vtkFloatArray *mcm_array = vtkFloatArray::New();

    typename MCMImageType::SizeType size = inputMCM->GetLargestPossibleRegion().GetSize();
    typename MCMImageType::SpacingType spacing = inputMCM->GetSpacing();
    typename MCMImageType::PointType  origin  = inputMCM->GetOrigin();
    typename TMCMImage::DirectionType directions = inputMCM->GetDirection();

    unsigned int numVoxels = inputMCM->GetLargestPossibleRegion().GetNumberOfPixels();
    double pt[3], sp[3];
    for (unsigned int i=0;i<3;++i)
    {
        pt[i] = 0; //do not use origin[i] coz if the directions does not match it wont be useful better keep em both in m_DirectionMatrix
        sp[i] = spacing[i];
    }

    m_VTKMCMData->SetDimensions(size[0],size[1],size[2]);
    m_VTKMCMData->SetSpacing(sp);
    m_VTKMCMData->SetOrigin(pt);

    for (int i=0;i<3;++i)
        for (int j=0;j<3;++j)
            m_DirectionMatrix->SetElement(i,j,directions(i,j));

    for (int i=0;i<3;++i)
        m_DirectionMatrix->SetElement(i,3,origin[i]);

    mcm_array->SetName(vtkMCMGlyph::GetMCMCoefficientsArrayName());
    mcm_array->SetNumberOfComponents(inputMCM->GetNumberOfComponentsPerPixel());
    mcm_array->SetNumberOfTuples(numVoxels);

    this->UpdateProgress(0.0);
    const unsigned long step = 0.15*numVoxels;
    int count = 0;

    typedef itk::ImageRegionConstIteratorWithIndex<MCMImageType> IteratorType;
    for (IteratorType it(inputMCM,inputMCM->GetLargestPossibleRegion());!it.IsAtEnd();++it)
    {
        MCMType mcmData = it.Get();
        mcm_array->InsertTuple(count,&mcmData[0]);

        if (++count%step==0)
            this->UpdateProgress(double(count)/double(numVoxels));
    }

    m_VTKMCMData->GetPointData()->AddArray(mcm_array);

    mcm_array->Delete();
    m_VTKMCMData->Update();
}

template <class TMCMImage>
vtkMatrix4x4* animaMCMITKToVTKFilter<TMCMImage>::GetDirectionMatrix() const
{
    return m_DirectionMatrix;
}
