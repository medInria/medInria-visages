#include <animaDataMCMImageDouble3.h>
#include <medAbstractDataFactory.h>

#include <itkImage.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkImageFileWriter.h>
#include <itkVectorImage.h>
#include <itkVector.h>

// /////////////////////////////////////////////////////////////////
// itkDataSHImagePrivate
// /////////////////////////////////////////////////////////////////

class animaDataMCMImageDouble3Private
{
public:
    typedef itk::VectorImage<double, 3> MCMImageType;
    typedef anima::MultiCompartmentModel::Pointer MCModelPointer;

    MCMImageType::Pointer mcmImage;
    MCModelPointer referenceModel;
};

// /////////////////////////////////////////////////////////////////
// itkDataSHImage
// /////////////////////////////////////////////////////////////////

animaDataMCMImageDouble3::animaDataMCMImageDouble3(): medAbstractTypedDiffusionModelImageData<3,double>(), d(new animaDataMCMImageDouble3Private)
{
    d->mcmImage = 0;
    d->referenceModel = 0;
}

animaDataMCMImageDouble3::~animaDataMCMImageDouble3()
{
    delete d;
    d = 0;
}

bool animaDataMCMImageDouble3::registered()
{
    return medAbstractDataFactory::instance()->registerDataType<animaDataMCMImageDouble3>();
}

void *animaDataMCMImageDouble3::data()
{
    return d->mcmImage.GetPointer();
}

void *animaDataMCMImageDouble3::output()
{
    return d->mcmImage.GetPointer();
}

void animaDataMCMImageDouble3::setData(void *data)
{
    typedef animaDataMCMImageDouble3Private::MCMImageType MCMImageType;

    if( MCMImageType* mcm = dynamic_cast<MCMImageType*>( (itk::Object*)(data) ) ){
        d->mcmImage = mcm;
    }
    else
      qDebug() << "Cannot cast pointer to correct SH double type";
}

void animaDataMCMImageDouble3::setReferenceModel(MCModelPointer &model)
{
    d->referenceModel = model;
}

animaDataMCMImageDouble3::MCModelPointer &animaDataMCMImageDouble3::getReferenceModel()
{
    return d->referenceModel;
}

int animaDataMCMImageDouble3::xDimension()
{
    if (!d->mcmImage.IsNull())
      return d->mcmImage->GetLargestPossibleRegion().GetSize()[0];
    return -1;
}

int animaDataMCMImageDouble3::yDimension()
{
    if (!d->mcmImage.IsNull())
        return d->mcmImage->GetLargestPossibleRegion().GetSize()[1];
    return -1;
}

int animaDataMCMImageDouble3::zDimension()
{
    if (!d->mcmImage.IsNull())
        return d->mcmImage->GetLargestPossibleRegion().GetSize()[2];
    return -1;
}
