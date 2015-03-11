/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <animaDESPOT1Relaxometry.h>

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medAbstractDataFactory.h>
#include <medAbstractData.h>
#include <medAbstractImageData.h>

#include <animaReadWriteFunctions.h>
#include <animaT1RelaxometryEstimationImageFilter.h>

// /////////////////////////////////////////////////////////////////
// animaDESPOT1RelaxometryPrivate
// /////////////////////////////////////////////////////////////////

class animaDESPOT1RelaxometryPrivate
{
public:
    dtkSmartPointer <medAbstractData> input;
    dtkSmartPointer <medAbstractImageData> output;

    template <class T> void update();

    double firstFlipAngle, secondFlipAngle;
    double trTime;
    double upperBoundM0, upperBoundT1;
    double backgroundSignalThreshold;
    double nbThreads;
};

template <class T>
void
animaDESPOT1RelaxometryPrivate::update()
{
    typedef itk::Image <T, 3> InputImageType;
    typedef itk::Image <double, 3> OutputImageType;
    typedef itk::Image <T, 4> Image4DType;

    typedef anima::T1RelaxometryEstimationImageFilter <InputImageType, OutputImageType> FilterType;

    typename FilterType::Pointer mainFilter = FilterType::New();

    Image4DType *inputImage = dynamic_cast<Image4DType *>((itk::Object*)(input->data()));

    std::vector <typename InputImageType::Pointer> inputData = anima::getImagesFromHigherDimensionImage<Image4DType,InputImageType> (inputImage);
    for (unsigned int i = 0;i < inputData.size();++i)
        mainFilter->SetInput(i,inputData[i]);

    std::vector <double> flipAngles(2,0);
    flipAngles[0] = firstFlipAngle;
    flipAngles[1] = secondFlipAngle;
    mainFilter->SetFlipAngles(flipAngles);

    mainFilter->SetTRValue(trTime);
    mainFilter->SetM0UpperBoundValue(upperBoundM0);
    mainFilter->SetT1UpperBoundValue(upperBoundT1);

    mainFilter->SetAverageSignalThreshold(backgroundSignalThreshold);
    mainFilter->SetNumberOfThreads(nbThreads);

    mainFilter->Update();

    OutputImageType::Pointer outputData = mainFilter->GetOutput();
    outputData->DisconnectPipeline();

    output = dynamic_cast <medAbstractImageData *> (medAbstractDataFactory::instance()->create ("itkDataImageDouble3"));
    output->setData(outputData);
}

// /////////////////////////////////////////////////////////////////
// animaDESPOT1Relaxometry
// /////////////////////////////////////////////////////////////////

animaDESPOT1Relaxometry::animaDESPOT1Relaxometry() : dtkAbstractProcess(), d(new animaDESPOT1RelaxometryPrivate)
{
    d->firstFlipAngle = 5 * M_PI / 180.0;
    d->secondFlipAngle = 30 * M_PI / 180.0;
    d->trTime = 15;
    d->upperBoundM0 = 5000;
    d->upperBoundT1 = 5000;

    d->backgroundSignalThreshold = 10;
    d->nbThreads = itk::MultiThreader::GetGlobalDefaultNumberOfThreads();
}

animaDESPOT1Relaxometry::~animaDESPOT1Relaxometry()
{
    
}

bool animaDESPOT1Relaxometry::registered()
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("animaDESPOT1Relaxometry", create);
}

QString animaDESPOT1Relaxometry::description() const
{
    return "animaDESPOT1Relaxometry";
}

void animaDESPOT1Relaxometry::setInputImage ( medAbstractData *data )
{
    if ( !data )
        return;
        
    d->input = data;
}    

void animaDESPOT1Relaxometry::setTRTime (double val)
{
    d->trTime = val;
}

void animaDESPOT1Relaxometry::setFirstFlipAngle (double val)
{
    d->firstFlipAngle = val;
}

void animaDESPOT1Relaxometry::setSecondFlipAngle (double val)
{
    d->secondFlipAngle = val;
}

void animaDESPOT1Relaxometry::setUpperBoundM0(double val)
{
    d->upperBoundM0 = val;
}

void animaDESPOT1Relaxometry::setUpperBoundT1(double val)
{
    d->upperBoundT1 = val;
}

void animaDESPOT1Relaxometry::setBackgroundSignalThreshold (double val)
{
    d->backgroundSignalThreshold = val;
}

void animaDESPOT1Relaxometry::setNumberOfThreads(unsigned int val)
{
    d->nbThreads = val;
}

int animaDESPOT1Relaxometry::update()
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

medAbstractData * animaDESPOT1Relaxometry::output()
{
    return ( d->output );
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *create()
{
    return new animaDESPOT1Relaxometry;
}
