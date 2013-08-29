// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaPyramidalBMRegistration.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include "itkImageRegistrationMethod.h"

#include "itkImage.h"
#include "itkResampleImageFilter.h"
#include "itkCastImageFilter.h"


#include "time.h"

// Include specific RPI implementation of the registration method
#include <rpiAnimaPyramidalBMRegistration.h>
#include <rpiCommonTools.hxx>



// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistrationPrivate
// /////////////////////////////////////////////////////////////////

class animaPyramidalBMRegistrationPrivate
{
public:
    animaPyramidalBMRegistration * proc;
    template <class PixelType>
    int update(void);
    
    template <typename PixelType>
    bool writeTransform(const QString& file);
    
    template <typename PixelType>
    void abort(void);
    
    static void eventCallback ( itk::Object *caller, const itk::EventObject& event, void *clientData );
    
    void * registrationMethod;
    
    QString initTransformFile;
    unsigned int blockSize;
    unsigned int blockSpacing;
    float stDevThreshold;
    unsigned int transform;
    unsigned int metric;  
    unsigned int optimizer;
    unsigned int maximumIterations;
    float minimalTransformError;
    unsigned int optimizerMaximumIterations;
    unsigned int histogramSize;
    double searchRadius;
    double searchAngleRadius;
    double searchSkewRadius;
    double searchScaleRadius;
    double finalRadius;
    double stepSize;
    double tranlateUpperBound;
    double angleUpperBound;
    double skewUpperBound;
    double scaleUpperBound;
    unsigned int agregator;
    bool weightedAgregation;
    bool blockCenteredRotations;
    unsigned int outputTransformType;
    float agregThreshold;
    float seStoppingThreshold;
    unsigned int numberOfPyramidLevels;
    unsigned int lastPyramidLevel;
    unsigned int numberOfThreads;
    
    animaPyramidalBMRegistration* parent;
    itk::CStyleCommand::Pointer callback;
    
};

// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistration
// /////////////////////////////////////////////////////////////////

animaPyramidalBMRegistration::animaPyramidalBMRegistration(void) : itkProcessRegistration(), d(new animaPyramidalBMRegistrationPrivate)
{
    d->proc = this;
    d->registrationMethod = NULL;
    
    d->blockSize = 5;
    d->blockSpacing = 5;
    d->stDevThreshold = 5;
    d->transform = Translation;
    d->metric = FastCorrelation;  
    d->optimizer = Newuoa;
    d->maximumIterations = 10;
    d->minimalTransformError = 0.01;
    d->optimizerMaximumIterations = 100;
    d->histogramSize = 128;
    d->searchRadius = 2;
    d->searchAngleRadius = 5;
    d->searchSkewRadius = 5;
    d->searchScaleRadius = 0.1;
    d->finalRadius = 0.001;
    d->stepSize = 1;
    d->tranlateUpperBound = 50;
    d->angleUpperBound = 180;
    d->skewUpperBound = 45;
    d->scaleUpperBound = 3;
    d->agregator = MEstimation;
    d->weightedAgregation = false;
    d->blockCenteredRotations = false;
    d->outputTransformType = outRigid;
    d->agregThreshold = 0.5;
    d->seStoppingThreshold = 0.01;
    d->numberOfPyramidLevels = 3;
    d->lastPyramidLevel = 0;
    d->numberOfThreads = 2;
    
    d->parent = this;
    this->setProperty("transformType","rigid");
}

animaPyramidalBMRegistration::~animaPyramidalBMRegistration(void)
{
    d->proc = NULL;

    typedef itk::Image< float, 3 >  RegImageType;
    
    if (d->registrationMethod)
        delete static_cast<rpi::AnimaPyramidalBMRegistration< RegImageType, RegImageType,double > *>(d->registrationMethod);

    d->registrationMethod = NULL;
    
    delete d;
    d = 0;
}

bool animaPyramidalBMRegistration::registered(void)
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("animaPyramidalBMRegistration",
                                                                 createAnimaPyramidalBMRegistration);
}

QString animaPyramidalBMRegistration::description(void) const
{
    return "Pyramidal BM Registration";
}

QString animaPyramidalBMRegistration::identifier(void) const
{
    return "animaPyramidalBMRegistration";
}

itk::Transform<double,3,3>::Pointer animaPyramidalBMRegistration::getTransform()
{
    typedef float PixelType;
    typedef double TransformScalarType;
    typedef itk::Image< PixelType, 3 > RegImageType;
    //normaly should use long switch cases, but here we know we work with float3 data.
    if (rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> * registration =
        static_cast<rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> *>(d->registrationMethod))
    {
        return registration->GetTransformation();
    }
    else
        return NULL;
}

QString animaPyramidalBMRegistration::getTitleAndParameters()
{
    typedef float PixelType;
    typedef double TransformScalarType;
    typedef itk::Image< PixelType, 3 > RegImageType;
    //normaly should use long switch cases, but here we know we work with float3 data.
    typedef rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> RegistrationType;
    RegistrationType * registration = static_cast<RegistrationType *>(d->registrationMethod);
    
    QString titleAndParameters;
    titleAndParameters += "Pyramidal BM Registration\n";
    titleAndParameters += " Number of pyramid levels: " + QString::number(registration->GetNumberOfPyramidLevels()) + "\n";
    titleAndParameters += " Number of iterations per level: " + QString::number(registration->GetMaximumIterations()) + "\n";

    //TO DO : add transform type and optimizer used to parameters given
    return titleAndParameters;
}

// /////////////////////////////////////////////////////////////////
// Templated Version of update
// /////////////////////////////////////////////////////////////////

void animaPyramidalBMRegistrationPrivate::eventCallback ( itk::Object* caller, const itk::EventObject& event, void* clientData )
{
    animaPyramidalBMRegistrationPrivate * source = reinterpret_cast<animaPyramidalBMRegistrationPrivate *> ( clientData );
    itk::ProcessObject * processObject = ( itk::ProcessObject* ) caller;

    if ( !source )
        qDebug() << "Source is null";

    source->parent->emitProgress((int) (processObject->GetProgress() * 100));
}

 
void animaPyramidalBMRegistration::emitProgress(int prog)
{
    emit progressed(prog);
}

template <typename PixelType>
int animaPyramidalBMRegistrationPrivate::update(void)
{
    typedef itk::Image< PixelType, 3 >  FixedImageType;
    typedef itk::Image< PixelType, 3 >  MovingImageType;
        
    typename rpi::AnimaPyramidalBMRegistration<FixedImageType,MovingImageType, double> * registration =
    new rpi::AnimaPyramidalBMRegistration<FixedImageType,MovingImageType,double> ();
    
    // set callback
    callback = itk::CStyleCommand::New();
    callback->SetClientData ( ( void * ) this );
    callback->SetCallback ( animaPyramidalBMRegistrationPrivate::eventCallback );
    registration->SetProgressCallback(callback);
    
    registrationMethod = registration;
    
    registration->SetFixedImage((const FixedImageType*) proc->fixedImage().GetPointer());
    registration->SetMovingImage((const MovingImageType*) proc->movingImages()[0].GetPointer());
    
    if(!initTransformFile.isEmpty())
       registration->SetInitialTransform( initTransformFile.toStdString() );
    
    registration->SetBlockSize( blockSize);
    registration->SetBlockSpacing( blockSpacing);
    registration->SetStDevThreshold( stDevThreshold);
    registration->SetTransform( transform);
    registration->SetMetric( metric);
    registration->SetOptimizer( optimizer);
    registration->SetMaximumIterations( maximumIterations);
    registration->SetMinimalTransformError( minimalTransformError);   
    registration->SetOptimizerMaximumIterations( optimizerMaximumIterations);    
    registration->SetHistogramSize( histogramSize);
    registration->SetSearchRadius( searchRadius);
    registration->SetSearchAngleRadius( searchAngleRadius);
    registration->SetSearchSkewRadius( searchSkewRadius);
    registration->SetSearchScaleRadius( searchScaleRadius);
    registration->SetFinalRadius( finalRadius);
    registration->SetStepSize( stepSize);
    registration->SetTranlateUpperBound( tranlateUpperBound);
    registration->SetAngleUpperBound( angleUpperBound);
    registration->SetSkewUpperBound( skewUpperBound);
    registration->SetScaleUpperBound( scaleUpperBound);
    registration->SetAgregator( agregator);
    registration->SetWeightedAgregation( weightedAgregation);
    registration->SetBlockCenteredRotations( blockCenteredRotations);
    registration->SetOutputTransformType( outputTransformType);    
    registration->SetAgregThreshold( agregThreshold);    
    registration->SetSeStoppingThreshold( seStoppingThreshold);
    registration->SetNumberOfPyramidLevels( numberOfPyramidLevels);
    registration->SetLastPyramidLevel( lastPyramidLevel);    
    registration->SetNumberOfThreads( numberOfThreads);
    
    
    // Run the registration
    time_t t1 = clock();
    try {
        registration->StartRegistration();
    }
    catch( std::exception & err )
    {
        qDebug() << "ExceptionObject caught ! (startRegistration)" << err.what();
        return 1;
    }
    
    time_t t2 = clock();
    
    qDebug() << "Elasped time: " << (double)(t2-t1)/(double)CLOCKS_PER_SEC;
    
    typedef itk::ResampleImageFilter< MovingImageType,MovingImageType,double >    ResampleFilterType;
    typename ResampleFilterType::Pointer resampler = ResampleFilterType::New();
    resampler->SetTransform(registration->GetTransformation());
    resampler->SetInput((const MovingImageType*)proc->movingImages()[0].GetPointer());
    resampler->SetSize( proc->fixedImage()->GetLargestPossibleRegion().GetSize() );
    resampler->SetOutputOrigin( proc->fixedImage()->GetOrigin() );
    resampler->SetOutputSpacing( proc->fixedImage()->GetSpacing() );
    resampler->SetOutputDirection( proc->fixedImage()->GetDirection() );
    resampler->SetDefaultPixelValue( 0 );
    
    
    try {
        resampler->Update();
    }
    catch (itk::ExceptionObject &e) {
        qDebug() << e.GetDescription();
        return 1;
    }
    
    itk::ImageBase<3>::Pointer result = resampler->GetOutput();
    result->DisconnectPipeline();
    
    if (proc->output())
        proc->output()->setData (result);
    return 0;
}

int animaPyramidalBMRegistration::update(itkProcessRegistration::ImageType imgType)
{
    if(fixedImage().IsNull() || movingImages()[0].IsNull())
        return 1;

    return d->update<float>();
}


template <typename PixelType>
bool animaPyramidalBMRegistrationPrivate::writeTransform(const QString& file)
{
    typedef double TransformScalarType;
    typedef itk::Image< PixelType, 3 > RegImageType;
    
    if (rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> * registration =
        static_cast<rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> *>(registrationMethod))
    {
        try
        {
            rpi::writeLinearTransformation<TransformScalarType, 3>(registration->GetTransformation(),
                                                                              file.toStdString());
            
        }
        catch (std::exception)
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
    
}

bool animaPyramidalBMRegistration::writeTransform(const QString& file)
{
    if(d->registrationMethod == NULL)
        return 1;
    
    return d->writeTransform<float>(file);
}


template <typename PixelType>
void animaPyramidalBMRegistrationPrivate::abort (void)
{  
    typedef double TransformScalarType;
    typedef itk::Image< PixelType, 3 > RegImageType;
    
    if (rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> * registration =
        static_cast<rpi::AnimaPyramidalBMRegistration<RegImageType,RegImageType,TransformScalarType> *>(registrationMethod)) 
    {
        registration->Abort();   
    }
}

void animaPyramidalBMRegistration::onCanceled (void)
{   
    if(d->registrationMethod != NULL)
        d->abort<float>();
}


void animaPyramidalBMRegistration::initTransformFile(QString initTransformFile)
{
    d->initTransformFile = initTransformFile;
}
   
void animaPyramidalBMRegistration::setBlockSize(int blockSize)
{
    d->blockSize=blockSize;
}

void animaPyramidalBMRegistration::setBlockSpacing(unsigned int blockSpacing) 
{
    d->blockSpacing=blockSpacing;
}

void animaPyramidalBMRegistration::setStDevThreshold(float StDevThreshold) 
{
    d->stDevThreshold=StDevThreshold;
}

void animaPyramidalBMRegistration::setTransform(unsigned int transform) 
{
    d->transform=transform;
}

void animaPyramidalBMRegistration::setMetric(unsigned int metric) 
{
    d->metric=metric;
}

void animaPyramidalBMRegistration::setOptimizer(unsigned int optimizer)
{
    d->optimizer=optimizer;
}

void animaPyramidalBMRegistration::setMaximumIterations(unsigned int MaximumIterations) 
{
    d->maximumIterations=MaximumIterations;
}

void animaPyramidalBMRegistration::setMinimalTransformError(float MinimalTransformError) 
{
    d->minimalTransformError=MinimalTransformError;
}

void animaPyramidalBMRegistration::setOptimizerMaximumIterations(unsigned int OptimizerMaximumIterations) 
{
    d->optimizerMaximumIterations=OptimizerMaximumIterations;
}

void animaPyramidalBMRegistration::setHistogramSize(unsigned int HistogramSize) 
{
    d->histogramSize=HistogramSize;
}

void animaPyramidalBMRegistration::setSearchRadius(double SearchRadius) 
{
    d->searchRadius=SearchRadius;
}

void animaPyramidalBMRegistration::setSearchAngleRadius(double SearchAngleRadius) 
{
    d->searchAngleRadius=SearchAngleRadius;
}

void animaPyramidalBMRegistration::setSearchSkewRadius(double SearchSkewRadius) 
{
    d->searchSkewRadius=SearchSkewRadius;
}

void animaPyramidalBMRegistration::setSearchScaleRadius(double SearchScaleRadius) 
{
    d->searchScaleRadius=SearchScaleRadius;
}

void animaPyramidalBMRegistration::setFinalRadius(double FinalRadius) 
{
    d->finalRadius=FinalRadius;
}

void animaPyramidalBMRegistration::setStepSize(double StepSize) 
{
    d->stepSize=StepSize;
}

void animaPyramidalBMRegistration::setTranlateUpperBound(double TranlateUpperBound) 
{
    d->tranlateUpperBound=TranlateUpperBound;
}

void animaPyramidalBMRegistration::setAngleUpperBound(double AngleUpperBound) 
{
    d->angleUpperBound=AngleUpperBound;
}

void animaPyramidalBMRegistration::setSkewUpperBound(double SkewUpperBound)
{
    d->skewUpperBound=SkewUpperBound;
}

void animaPyramidalBMRegistration::setScaleUpperBound(double ScaleUpperBound) 
{
    d->scaleUpperBound=ScaleUpperBound;
}

void animaPyramidalBMRegistration::setAgregator(unsigned int agregator)
{
    d->agregator=agregator;
}

void animaPyramidalBMRegistration::setWeightedAgregation(bool WeightedAgregation) 
{
    d->weightedAgregation=WeightedAgregation;
}

void animaPyramidalBMRegistration::setBlockCenteredRotations(bool BlockCenteredRotations) 
{
    d->blockCenteredRotations=BlockCenteredRotations;
}

void animaPyramidalBMRegistration::setOutputTransformType(unsigned int outputTransform)
{
   d-> outputTransformType=outputTransform;
}

void animaPyramidalBMRegistration::setAgregThreshold(float AgregThreshold)
{
    d->agregThreshold=AgregThreshold;
}

void animaPyramidalBMRegistration::setSeStoppingThreshold(float SeStoppingThreshold)
{
    d->seStoppingThreshold=SeStoppingThreshold;
}

void animaPyramidalBMRegistration::setNumberOfPyramidLevels(unsigned int NumberOfPyramidLevels)
{
    d->numberOfPyramidLevels=NumberOfPyramidLevels;
}

void animaPyramidalBMRegistration::setLastPyramidLevel(unsigned int LastPyramidLevel) 
{
    d->lastPyramidLevel=LastPyramidLevel;
}

void animaPyramidalBMRegistration::setNumberOfThreads(int numberOfThreads) 
{
    d->numberOfThreads=numberOfThreads;
}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createAnimaPyramidalBMRegistration(void)
{
    return new animaPyramidalBMRegistration;
}



