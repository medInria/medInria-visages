#include <animaT2RelaxometryProcess.h>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>
#include <medDataManager.h>
#include <itkCommand.h>

#include <animaT2RelaxometryEstimationImageFilter.h>
#include <animaReadWriteFunctions.h>

animaT2RelaxometryProcess::animaT2RelaxometryProcess(QObject *parent)
    : medAbstractRelaxometryEstimationProcess(parent)
{
    m_t2filter = 0;

    m_trTime = new medDoubleParameter("tr_time", this);
    m_trTime->setCaption("Acq. TR time:");
    m_trTime->setDescription("Acquisition TR time (in ms)");
    m_trTime->setRange(0,10000);
    m_trTime->setValue(4500);

    m_echoSpacing = new medDoubleParameter("echo_spacing", this);
    m_echoSpacing->setCaption("Echo spacing:");
    m_echoSpacing->setDescription("Echo spacing");
    m_echoSpacing->setRange(0,100);
    m_echoSpacing->setValue(10);

    m_upperBoundT2 = new medDoubleParameter("t2_upper", this);
    m_upperBoundT2->setCaption("Upper bound T2:");
    m_upperBoundT2->setDescription("T2 upper bound value");
    m_upperBoundT2->setRange(0,10000);
    m_upperBoundT2->setValue(800);

    m_backgroundSignalThreshold = new medDoubleParameter("bg_threshold", this);
    m_backgroundSignalThreshold->setCaption("Signal threshold:");
    m_backgroundSignalThreshold->setDescription("Background signal threshold");
    m_backgroundSignalThreshold->setRange(0,1000);
    m_backgroundSignalThreshold->setValue(10);

    m_T1Map = 0;
}

animaT2RelaxometryProcess::~animaT2RelaxometryProcess()
{
    
}

medDoubleParameter *animaT2RelaxometryProcess::trTime() const
{
    return m_trTime;
}

medDoubleParameter *animaT2RelaxometryProcess::echoSpacing() const
{
    return m_echoSpacing;
}

medDoubleParameter *animaT2RelaxometryProcess::upperBoundT2() const
{
    return m_upperBoundT2;
}

medDoubleParameter *animaT2RelaxometryProcess::backgroundSignalThreshold() const
{
    return m_backgroundSignalThreshold;
}

QString animaT2RelaxometryProcess::caption() const
{
    return "T2 Relaxometry";
}

QString animaT2RelaxometryProcess::description() const
{
    return "T2 relaxometry map estimation";
}

void animaT2RelaxometryProcess::setT1Map (const medDataIndex &index)
{
    medAbstractImageData *t1Map = dynamic_cast <medAbstractImageData *> (medDataManager::instance()->retrieveData(index));

    if (!t1Map)
        return;

    m_T1Map = t1Map;
}

medAbstractJob::medJobExitStatus animaT2RelaxometryProcess::run()
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
medAbstractJob::medJobExitStatus animaT2RelaxometryProcess::_run()
{
    typedef itk::Image <PixelType, 3> InputImageType;
    typedef itk::Image <double, 3> OutputImageType;
    typedef itk::Image <PixelType, 4> Image4DType;

    typedef anima::T2RelaxometryEstimationImageFilter <InputImageType, OutputImageType> FilterType;

    typename FilterType::Pointer mainFilter = FilterType::New();

    Image4DType *inputImage = dynamic_cast<Image4DType *>((itk::Object*)(this->input()->data()));

    std::vector <typename InputImageType::Pointer> inputData = anima::getImagesFromHigherDimensionImage<Image4DType,InputImageType> (inputImage);
    for (unsigned int i = 0;i < inputData.size();++i)
        mainFilter->SetInput(i,inputData[i]);

    unsigned int numInputs = mainFilter->GetNumberOfIndexedInputs();
    std::vector<double> echoTime(numInputs);

    for(unsigned int index = 0;index < echoTime.size();++index)
        echoTime[index]=(index+1)*(m_echoSpacing->value());

    mainFilter->SetEchoSpacing(m_echoSpacing->value());

    mainFilter->SetTRValue(m_trTime->value());
    mainFilter->SetT2UpperBoundValue(m_upperBoundT2->value());

    if (m_T1Map)
    {
        OutputImageType *t1MapData = dynamic_cast<OutputImageType *>((itk::Object*)(m_T1Map->data()));
        if (t1MapData)
            mainFilter->SetT1Map(t1MapData);
    }

    mainFilter->SetAverageSignalThreshold(m_backgroundSignalThreshold->value());

    m_t2filter = mainFilter;

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaT2RelaxometryProcess::eventCallback);

    m_t2filter->AddObserver(itk::ProgressEvent(), callback);

    try
    {
        m_t2filter->Update();
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

void animaT2RelaxometryProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_t2filter.IsNotNull())
            m_t2filter->AbortGenerateDataOn();
    }
}
