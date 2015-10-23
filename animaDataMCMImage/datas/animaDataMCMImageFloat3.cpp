#include <animaDataMCMImageFloat3.h>

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

class animaDataMCMImageFloat3Private
{
public:
    typedef itk::VectorImage<float, 3> MCMImageType;
    typedef anima::MultiCompartmentModel::Pointer MCModelPointer;

    MCMImageType::Pointer mcmImage;
    MCModelPointer referenceModel;
};

// /////////////////////////////////////////////////////////////////
// itkDataSHImage
// /////////////////////////////////////////////////////////////////

animaDataMCMImageFloat3::animaDataMCMImageFloat3(): medAbstractTypedDiffusionModelImageData<3,float>(), d(new animaDataMCMImageFloat3Private)
{
    d->mcmImage = 0;
    d->referenceModel = 0;
}

animaDataMCMImageFloat3::~animaDataMCMImageFloat3()
{
    delete d;
    d = 0;
}

bool animaDataMCMImageFloat3::registered()
{
    return medAbstractDataFactory::instance()->registerDataType<animaDataMCMImageFloat3>();
}

void *animaDataMCMImageFloat3::data()
{
    return d->mcmImage.GetPointer();
}

void *animaDataMCMImageFloat3::output()
{
    return d->mcmImage.GetPointer();
}

void animaDataMCMImageFloat3::setData(void *data)
{
    typedef animaDataMCMImageFloat3Private::MCMImageType MCMImageType;

    if( MCMImageType* mcm = dynamic_cast<MCMImageType*>( (itk::Object*)(data) ) ){
        d->mcmImage = mcm;
    }
    else
      qDebug() << "Cannot cast pointer to correct MCM float type";
}

void animaDataMCMImageFloat3::setReferenceModel(MCModelPointer &model)
{
    d->referenceModel = model;
}

animaDataMCMImageFloat3::MCModelPointer &animaDataMCMImageFloat3::getReferenceModel()
{
    return d->referenceModel;
}

int animaDataMCMImageFloat3::xDimension()
{
    if (!d->mcmImage.IsNull())
      return d->mcmImage->GetLargestPossibleRegion().GetSize()[0];
    return -1;
}

int animaDataMCMImageFloat3::yDimension()
{
    if (!d->mcmImage.IsNull())
        return d->mcmImage->GetLargestPossibleRegion().GetSize()[1];
    return -1;
}

int animaDataMCMImageFloat3::zDimension()
{
    if (!d->mcmImage.IsNull())
        return d->mcmImage->GetLargestPossibleRegion().GetSize()[2];
    return -1;
}
