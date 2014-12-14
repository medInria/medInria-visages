#pragma once

#include <itkImage.h>
#include <itkImageToImageFilter.h>

class vtkImageData;
class vtkMatrix4x4;

/** \class animaMCMITKToVTKFilter
 * \brief  Convert an anima MCM image into a VTK structured points
 *
 * \ingroup   ImageFilter
 */
template < class TMCMImage >
class animaMCMITKToVTKFilter
        : public itk::ImageToImageFilter< TMCMImage, TMCMImage >
{
public:
    /** Some typedefs. */
    typedef TMCMImage MCMImageType;
    typedef typename  MCMImageType::PixelType MCMType;
    typedef typename  MCMType::ValueType ScalarType;
    typedef typename  MCMImageType::Pointer MCMImagePointer;
    typedef typename  MCMImageType::ConstPointer MCMImageConstPointer;

    /** Standard class typedefs. */
    typedef animaMCMITKToVTKFilter Self;
    typedef itk::ImageToImageFilter<MCMImageType,MCMImageType> Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<const Self> ConstPointer;

    /** Method for creation through the object factory. */
    itkNewMacro(Self);

    /** Run-time type information (and related methods). */
    itkTypeMacro(animaMCMITKToVTKFilter, ImageToImageFilter);

    /** Return the input (no ITK filtering is performed on the input image) */
    MCMImageType *GetOutput();

    /** Get the VTK SphericalHarmonic image obtained from the input ITK MCM image */
    void CopyVTKSphericalHarmonic(vtkImageData *);

    vtkImageData* GetVTKMCMData() const
    { return m_VTKMCMData; }

    /** Get the VTKMatrix4x4 obtained from the Itk image transformation that
     *  defines the image coordinate system*/
    vtkMatrix4x4 *GetDirectionMatrix() const;

protected:
    animaMCMITKToVTKFilter();
    virtual ~animaMCMITKToVTKFilter();

    /** Method that actually read the ITK data and convert it into a
     *  VTK structured point */
    virtual void GenerateData();

private:
    animaMCMITKToVTKFilter(const Self&); //purposely not implemented
    void operator=(const Self&); //purposely not implemented

    /** VTK output */
    vtkImageData* m_VTKMCMData;

    vtkMatrix4x4 *m_DirectionMatrix;

};

#include "animaMCMITKToVTKFilter.hxx"
