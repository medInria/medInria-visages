/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <animaT2Relaxometry.h>

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medAbstractDataFactory.h>
#include <medAbstractData.h>
#include <medAbstractImageData.h>

#include <animaReadWriteFunctions.h>
#include <animaT2RelaxometryEstimationImageFilter.h>

// /////////////////////////////////////////////////////////////////
// animaT2RelaxometryPrivate
// /////////////////////////////////////////////////////////////////

class animaT2RelaxometryPrivate
{
public:
    dtkSmartPointer <medAbstractData> input;
    dtkSmartPointer <medAbstractImageData> output;
    dtkSmartPointer <medAbstractImageData> t1Map;

    template <class T> void update();

    double echoSpacing;
    double trTime;
    double upperBoundM0, upperBoundT2;
    double backgroundSignalThreshold;
    double nbThreads;
};

template <class T>
void
animaT2RelaxometryPrivate::update()
{
    typedef itk::Image <T, 3> InputImageType;
    typedef itk::Image <double, 3> OutputImageType;
    typedef itk::Image <T, 4> Image4DType;

    typedef anima::T2RelaxometryEstimationImageFilter <InputImageType, OutputImageType> FilterType;

    typename FilterType::Pointer mainFilter = FilterType::New();

    Image4DType *inputImage = dynamic_cast<Image4DType *>((itk::Object*)(input->data()));

    std::vector <typename InputImageType::Pointer> inputData = anima::getImagesFromHigherDimensionImage<Image4DType,InputImageType> (inputImage);
    for (unsigned int i = 0;i < inputData.size();++i)
        mainFilter->SetInput(i,inputData[i]);

    mainFilter->SetEchoSpacing(echoSpacing);

    mainFilter->SetTRValue(trTime);
    mainFilter->SetM0UpperBoundValue(upperBoundM0);
    mainFilter->SetT2UpperBoundValue(upperBoundT2);

    if (t1Map)
    {
        OutputImageType *t1MapData = dynamic_cast<OutputImageType *>((itk::Object*)(t1Map->data()));
        if (t1MapData)
            mainFilter->SetT1Map(t1MapData);
    }

    mainFilter->SetAverageSignalThreshold(backgroundSignalThreshold);
    mainFilter->SetNumberOfThreads(nbThreads);

    mainFilter->Update();

    OutputImageType::Pointer outputData = mainFilter->GetOutput();
    outputData->DisconnectPipeline();

    output = dynamic_cast <medAbstractImageData *> (medAbstractDataFactory::instance()->create ("itkDataImageDouble3"));
    output->setData(outputData);
}

// /////////////////////////////////////////////////////////////////
// animaT2Relaxometry
// /////////////////////////////////////////////////////////////////

animaT2Relaxometry::animaT2Relaxometry() : dtkAbstractProcess(), d(new animaT2RelaxometryPrivate)
{
    d->echoSpacing = 10;
    d->trTime = 4500;
    d->upperBoundM0 = 5000;
    d->upperBoundT2 = 5000;

    d->backgroundSignalThreshold = 10;
    d->nbThreads = itk::MultiThreader::GetGlobalDefaultNumberOfThreads();
    d->t1Map = 0;
}

animaT2Relaxometry::~animaT2Relaxometry()
{
    
}

bool animaT2Relaxometry::registered()
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("animaT2Relaxometry", createAnimaT2Relaxometry);
}

QString animaT2Relaxometry::description() const
{
    return "animaT2Relaxometry";
}

void animaT2Relaxometry::setInputImage ( medAbstractData *data )
{
    if ( !data )
        return;

    d->input = data;
}    

void animaT2Relaxometry::setT1Map ( medAbstractImageData *data )
{
    if ( !data )
        return;

    d->t1Map = data;
}

void animaT2Relaxometry::setTRTime (double val)
{
    d->trTime = val;
}

void animaT2Relaxometry::setEchoSpacing (double val)
{
    d->echoSpacing = val;
}

void animaT2Relaxometry::setUpperBoundM0(double val)
{
    d->upperBoundM0 = val;
}

void animaT2Relaxometry::setUpperBoundT2(double val)
{
    d->upperBoundT2 = val;
}

void animaT2Relaxometry::setBackgroundSignalThreshold (double val)
{
    d->backgroundSignalThreshold = val;
}

void animaT2Relaxometry::setNumberOfThreads(unsigned int val)
{
    d->nbThreads = val;
}

int animaT2Relaxometry::update()
{
    if ( !d->input )
        return -1;

    medAbstractImageData *imageData = dynamic_cast <medAbstractImageData *> (d->input.data());

    if (!imageData)
        return -1;

    if (imageData->Dimension() != 4)
        return -1;

    QString type = imageData->identifier();
    if ( type.contains("itkDataImageChar"))
    {
        d->update<char>();
    }
    else if ( type.contains("itkDataImageUChar"))
    {
        d->update<unsigned char>();
    }
    else if ( type.contains("itkDataImageShort"))
    {
        d->update<short>();
    }
    else if ( type.contains("itkDataImageUShort"))
    {
        d->update<unsigned short>();
    }
    else if ( type.contains("itkDataImageInt"))
    {
        d->update<int>();
    }
    else if ( type.contains("itkDataImageUInt"))
    {
        d->update<unsigned int>();
    }
    else if ( type.contains("itkDataImageLong"))
    {
        d->update<long>();
    }
    else if ( type.contains("itkDataImageULong"))
    {
        d->update<unsigned long>();
    }
    else if ( type.contains("itkDataImageFloat"))
    {
        d->update<float>();
    }
    else if ( type.contains("itkDataImageDouble"))
    {
        d->update<double>();
    }
    else
        return -1;
    
    return EXIT_SUCCESS;
}        

medAbstractData * animaT2Relaxometry::output()
{
    return ( d->output );
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createAnimaT2Relaxometry()
{
    return new animaT2Relaxometry;
}
