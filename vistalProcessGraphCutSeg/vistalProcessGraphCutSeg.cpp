// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessGraphCutSeg.h"

#include <itkImage.h>
#include <itkImageRegionIterator.h>

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkSmartPointer.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

#include "GraphCut_class.hh"

// /////////////////////////////////////////////////////////////////
// vistalProcessGraphCutSegPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessGraphCutSegPrivate
{

public:

    int image_count;

    QList<dtkAbstractData *> images;
    dtkSmartPointer<dtkAbstractData> mask;
    dtkSmartPointer<dtkAbstractData> output;

    dtkSmartPointer<dtkAbstractData> mask_inside;
    dtkSmartPointer<dtkAbstractData> mask_outside;

    double alpha;
    double beta;
    double sigma;
};

////////////////////////////////////////////////////
// vistalProcessGraphCutSeg
////////////////////////////////////////////////////

vistalProcessGraphCutSeg::vistalProcessGraphCutSeg(void) : dtkAbstractProcess(), d(new vistalProcessGraphCutSegPrivate)
{
    d->image_count = 0;

    d->alpha = 1;
    d->beta = 0;
    d->sigma = 0.6;
}

vistalProcessGraphCutSeg::~vistalProcessGraphCutSeg(void)
{
    delete d;
    d = NULL;
}


bool vistalProcessGraphCutSeg::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("vistalProcessGraphCutSeg", createVistalProcessGraphCutSeg);
}

QString vistalProcessGraphCutSeg::description(void) const
{
    return "GraphCut Segmentation Process";
}

QString vistalProcessGraphCutSeg::identifier(void) const
{
    return "vistalProcessGraphCutSeg";
}

void vistalProcessGraphCutSeg::setInput(dtkAbstractData *data, int channel)
{
        if(!d->image_count)
            return;

        switch (channel){

            case 0:
                d->mask = data;
                if (!d->mask)
                    qDebug() << "DEBUG : vistalProcessGraphCutSeg::setInput(.) mask input conversion failed";
                    return;

                break;
            case 1:
                d->images.append(data->convert("vistalDataImageFloat3"));
                break;
        }
}

void vistalProcessGraphCutSeg::setParameter(double data, int channel)
{
    switch (channel){

        case 0:
            d->image_count = (int) data;
            break;
        case 1:
            d->alpha = data;
            break;
        case 2:
            d->beta = data;
            break;
        case 3:
            d->sigma = data;
            break;
        default:
            return;
    }
}

int vistalProcessGraphCutSeg::update(void)
{
    if((!d->mask) || (d->image_count != d->images.size() ))
    {
        qDebug() << "No mask or not the right number of images" << d->image_count << d->images.size();
        return -1;
    }
    
    createSeparatedMasks <char> ();
    createSeparatedMasks <unsigned char> ();
    createSeparatedMasks <short> ();
    createSeparatedMasks <unsigned short> ();
    createSeparatedMasks <int> ();
    createSeparatedMasks <unsigned int> ();
    createSeparatedMasks <long> ();
    createSeparatedMasks <unsigned long> ();
    createSeparatedMasks <float> ();
    createSeparatedMasks <double> ();

    if (!d->images[0]){
        qDebug() << "DEBUG : method update() : d->images[0] is NULL";
        return -1;
    }

    vistal::GraphCuts *graphcuts = new vistal::GraphCuts;

    if(graphcuts == NULL)
        return -1;

    for(int i = 0 ; i < d->images.size() ; i++)
    {
        graphcuts->setInput(static_cast<vistal::Image3D<float> * > (d->images[i]->data()));
    }
    
    // Do real stuff here
    
    qDebug() << ((static_cast<vistal::Image3D<unsigned char> * > (d->mask_inside->data())) == NULL);
    qDebug() << ((static_cast<vistal::Image3D<unsigned char> * > (d->mask_outside->data())) == NULL);
    
    graphcuts->setTarget(static_cast<vistal::Image3D<unsigned char> * > (d->mask_inside->data()));
    graphcuts->setSink(static_cast<vistal::Image3D<unsigned char> * > (d->mask_outside->data()));
    
    graphcuts->setTLinkMode(vistal::Tlinks::Density);
    graphcuts->useSpectralGradient(false);
    
    graphcuts->setAlpha(d->alpha);
    graphcuts->setBeta(d->beta);
    graphcuts->setSigma(d->sigma);
    
    graphcuts->run();
    
    vistal::Image3D<unsigned char> *output = new vistal::Image3D<unsigned char> (*(graphcuts->getOutput()));
    
    d->output = dtkAbstractDataFactory::instance()->createSmartPointer("vistalDataImageUChar3");
    d->output->setData(output);

    delete graphcuts;
    
    return 0;
}

dtkAbstractData * vistalProcessGraphCutSeg::output(void)
{	
	return d->output;
}

template <typename PixelType>
    void vistalProcessGraphCutSeg::createSeparatedMasks (void)
    {
        typedef itk::Image< PixelType, 3 > ImageType;

        ImageType *tmpPtr = dynamic_cast<ImageType *> ((itk::Object*)(d->mask->data()));

        if(!tmpPtr)
            return;

        typedef itk::Image< unsigned char, 3 > OutputMaskType;

        OutputMaskType::Pointer maskInsideData = OutputMaskType::New();

        maskInsideData->Initialize();
        maskInsideData->SetRegions(tmpPtr->GetLargestPossibleRegion() );
        maskInsideData->SetOrigin( tmpPtr->GetOrigin() );
        maskInsideData->SetSpacing( tmpPtr->GetSpacing() );
        maskInsideData->SetDirection( tmpPtr->GetDirection() );
        maskInsideData->Allocate();

        OutputMaskType::Pointer maskOutsideData = OutputMaskType::New();

        maskOutsideData->Initialize();
        maskOutsideData->SetRegions(tmpPtr->GetLargestPossibleRegion() );
        maskOutsideData->SetOrigin( tmpPtr->GetOrigin() );
        maskOutsideData->SetSpacing( tmpPtr->GetSpacing() );
        maskOutsideData->SetDirection( tmpPtr->GetDirection() );
        maskOutsideData->Allocate();

        typedef itk::ImageRegionIterator<ImageType> MaskIteratorType;

        typedef itk::ImageRegionIterator<OutputMaskType> OutputMaskIteratorType;

        MaskIteratorType maskIterator(tmpPtr,tmpPtr->GetLargestPossibleRegion());

        OutputMaskIteratorType insideMaskIterator(maskInsideData, maskInsideData->GetLargestPossibleRegion());

        OutputMaskIteratorType outsideMaskIterator(maskOutsideData, maskOutsideData->GetLargestPossibleRegion());

        while(!maskIterator.IsAtEnd()){

            insideMaskIterator.Set(0);
            outsideMaskIterator.Set(0);

            if(maskIterator.Get() == 1)
                insideMaskIterator.Set(1);

            else if (maskIterator.Get() == 2)
                outsideMaskIterator.Set(1);

            ++maskIterator;
            ++insideMaskIterator;
            ++outsideMaskIterator;
        }

        /*
        if(!d->mask_inside)
            d->mask_inside = dtkAbstractDataFactory::instance()->createSmartPointer("vistalDataImageChar3");

        if(!d->mask_outside)
            d->mask_outside = dtkAbstractDataFactory::instance()->createSmartPointer("vistalDataImageChar3");
        */

        dtkSmartPointer<dtkAbstractData> tempMaskInside = dtkAbstractDataFactory::instance()->createSmartPointer("itkDataImageUChar3");

        dtkSmartPointer<dtkAbstractData> tempMaskOutside = dtkAbstractDataFactory::instance()->createSmartPointer("itkDataImageUChar3");

        tempMaskInside->setData(maskInsideData);

        tempMaskOutside->setData(maskOutsideData);

        d->mask_inside = tempMaskInside->convert("vistalDataImageUChar3");

        d->mask_outside = tempMaskOutside->convert("vistalDataImageUChar3");
    }

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createVistalProcessGraphCutSeg(void)
{
    return new vistalProcessGraphCutSeg;
}
