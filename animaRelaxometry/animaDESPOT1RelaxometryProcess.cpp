#include <animaDESPOT1RelaxometryProcess.h>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>
#include <itkCommand.h>

#include <animaT1RelaxometryEstimationImageFilter.h>
#include <animaReadWriteFunctions.h>

animaDESPOT1RelaxometryProcess::animaDESPOT1RelaxometryProcess(QObject *parent)
    : medAbstractRelaxometryEstimationProcess(parent)
{
    m_despot1filter = 0;

    m_firstFlipAngle = new medDoubleParameter("first_flip_angle", this);
    m_firstFlipAngle->setCaption("First flip angle:");
    m_firstFlipAngle->setDescription("First flip angle (in degrees)");
    m_firstFlipAngle->setRange(0,180);
    m_firstFlipAngle->setValue(5);

    m_secondFlipAngle = new medDoubleParameter("second_flip_angle", this);
    m_secondFlipAngle->setCaption("Second flip angle:");
    m_secondFlipAngle->setDescription("Second flip angle (in degrees)");
    m_secondFlipAngle->setRange(0,180);
    m_secondFlipAngle->setValue(30);

    m_trTime = new medDoubleParameter("tr_time", this);
    m_trTime->setCaption("Acq. TR time:");
    m_trTime->setDescription("Acquisition TR time (in ms)");
    m_trTime->setRange(0,500);
    m_trTime->setValue(15);

    m_upperBoundM0 = new medDoubleParameter("m0_upper", this);
    m_upperBoundM0->setCaption("Upper bound M0:");
    m_upperBoundM0->setDescription("M0 upper bound value");
    m_upperBoundM0->setRange(0,10000);
    m_upperBoundM0->setValue(5000);

    m_upperBoundT1 = new medDoubleParameter("t1_upper", this);
    m_upperBoundT1->setCaption("Upper bound T1:");
    m_upperBoundT1->setDescription("T1 upper bound value");
    m_upperBoundT1->setRange(0,10000);
    m_upperBoundT1->setValue(5000);

    m_backgroundSignalThreshold = new medDoubleParameter("bg_threshold", this);
    m_backgroundSignalThreshold->setCaption("Signal threshold:");
    m_backgroundSignalThreshold->setDescription("Background signal threshold");
    m_backgroundSignalThreshold->setRange(0,1000);
    m_backgroundSignalThreshold->setValue(10);
}

animaDESPOT1RelaxometryProcess::~animaDESPOT1RelaxometryProcess()
{
    
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::firstFlipAngle() const
{
    return m_firstFlipAngle;
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::secondFlipAngle() const
{
    return m_secondFlipAngle;
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::trTime() const
{
    return m_trTime;
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::upperBoundM0() const
{
    return m_upperBoundM0;
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::upperBoundT1() const
{
    return m_upperBoundT1;
}

medDoubleParameter *animaDESPOT1RelaxometryProcess::backgroundSignalThreshold() const
{
    return m_backgroundSignalThreshold;
}

QString animaDESPOT1RelaxometryProcess::caption() const
{
    return "DESPOT1 Relaxometry";
}

QString animaDESPOT1RelaxometryProcess::description() const
{
    return "T1 relaxometry map estimation (DESPOT1 algorithm)";
}

medAbstractJob::medJobExitStatus animaDESPOT1RelaxometryProcess::run()
{
    QString type = this->input()->identifier();
    unsigned int nbDimension = (*(type.end() - 1)).digitValue();

    if (nbDimension != 4)
        return medAbstractJob::MED_JOB_EXIT_FAILURE;

    medAbstractImageData *out = qobject_cast <medAbstractImageData *> (medAbstractDataFactory::instance()->create("itkDataImageDouble3"));
    this->setOutput(out);

    if (type.contains("itkDataImageChar"))
    {
        this->_run<char>();
    }
    else if (type.contains("itkDataImageUChar"))
    {
        this->_run<unsigned char>();
    }
    else if (type.contains("itkDataImageShort"))
    {
        this->_run<short>();
    }
    else if (type.contains("itkDataImageUShort"))
    {
        this->_run<unsigned short>();
    }
    else if (type.contains("itkDataImageInt"))
    {
        this->_run<int>();
    }
    else if (type.contains("itkDataImageUInt"))
    {
        this->_run<unsigned int>();
    }
    else if (type.contains("itkDataImageLong"))
    {
        this->_run<long>();
    }
    else if (type.contains("itkDataImageULong"))
    {
        this->_run<unsigned long>();
    }
    else if (type.contains("itkDataImageFloat"))
    {
        this->_run<float>();
    }
    else if (type.contains("itkDataImageDouble"))
    {
        this->_run<double>();
    }
    
    return medAbstractJob::MED_JOB_EXIT_FAILURE;
}

template <class PixelType>
medAbstractJob::medJobExitStatus animaDESPOT1RelaxometryProcess::_run()
{
    typedef itk::Image <PixelType, 3> InputImageType;
    typedef itk::Image <double, 3> OutputImageType;
    typedef itk::Image <PixelType, 4> Image4DType;
    typedef anima::T1RelaxometryEstimationImageFilter <InputImageType, OutputImageType> FilterType;

    typename FilterType::Pointer mainFilter = FilterType::New();

    Image4DType *inputImage = dynamic_cast<Image4DType *>((itk::Object*)(this->input()->data()));

    std::vector <typename InputImageType::Pointer> inputData = anima::getImagesFromHigherDimensionImage<Image4DType,InputImageType> (inputImage);
    for (unsigned int i = 0;i < inputData.size();++i)
        mainFilter->SetInput(i,inputData[i]);

    std::vector <double> flipAngles(2,0);
    flipAngles[0] = m_firstFlipAngle->value() * M_PI / 180.0;
    flipAngles[1] = m_secondFlipAngle->value() * M_PI / 180.0;
    mainFilter->SetFlipAngles(flipAngles);

    mainFilter->SetTRValue(m_trTime->value());
    mainFilter->SetM0UpperBoundValue(m_upperBoundM0->value());
    mainFilter->SetT1UpperBoundValue(m_upperBoundT1->value());

    mainFilter->SetAverageSignalThreshold(m_backgroundSignalThreshold->value());

    m_despot1filter = mainFilter;

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaDESPOT1RelaxometryProcess::eventCallback);

    m_despot1filter->AddObserver(itk::ProgressEvent(), callback);

    // process image
    try
    {
        m_despot1filter->Update();
    }
    catch(itk::ProcessAborted &e)
    {
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    // retrieve results (images and transforms)
    medAbstractImageData *out = this->output();
    out->setData(mainFilter->GetOutput());

    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

void animaDESPOT1RelaxometryProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_despot1filter.IsNotNull())
            m_despot1filter->AbortGenerateDataOn();
    }
}
