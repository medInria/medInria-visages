#include <animaSymmetryPlaneProcess.h>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>
#include <itkCommand.h>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>

#include <animaPyramidalSymmetryBridge.h>

animaSymmetryPlaneProcess::animaSymmetryPlaneProcess(QObject *parent)
    : medAbstractSymmetryPlaneAlignmentProcess(parent)
{
    m_symmetryplanebridge = nullptr;
    m_outputRealignTransform = nullptr;

    m_Metric = 1;

    m_optimizerMaximumIterations = new medIntParameter("max_opt_iter", this);
    m_optimizerMaximumIterations->setCaption("Max optimizer iterations");
    m_optimizerMaximumIterations->setDescription("Maximum Local Optimizer Iterations");
    m_optimizerMaximumIterations->setRange(1,200);
    m_optimizerMaximumIterations->setValue(100);

    m_histogramSize = new medIntParameter("mi_histo_size", this);
    m_histogramSize->setCaption("Histogram size");
    m_histogramSize->setDescription("Histogram size for mutual information");
    m_histogramSize->setRange(1,256);
    m_histogramSize->setValue(128);

    m_pyramidLevelsNumber = new medIntParameter("pyr_levels", this);
    m_pyramidLevelsNumber->setCaption("Pyramid levels");
    m_pyramidLevelsNumber->setDescription("Number of pyramid levels");
    m_pyramidLevelsNumber->setRange(1,10);
    m_pyramidLevelsNumber->setValue(3);

    m_upperBoundAngle = new medDoubleParameter("upper_angle", this);
    m_upperBoundAngle->setCaption("Angles upper");
    m_upperBoundAngle->setDescription("Upper bound on angles");
    m_upperBoundAngle->setRange(0.0,180.0);
    m_upperBoundAngle->setValue(180.0);

    m_upperBoundDistance = new medDoubleParameter("upper_distance", this);
    m_upperBoundDistance->setCaption("Translate upper");
    m_upperBoundDistance->setDescription("Upper bound on distance (in voxels)");
    m_upperBoundDistance->setRange(0.0,10.0);
    m_upperBoundDistance->setValue(6.0);
}

animaSymmetryPlaneProcess::~animaSymmetryPlaneProcess()
{
}

int animaSymmetryPlaneProcess::metric() const
{
    return m_Metric;
}

medIntParameter *animaSymmetryPlaneProcess::optimizerMaximumIterations() const
{
    return m_optimizerMaximumIterations;
}

medIntParameter *animaSymmetryPlaneProcess::histogramSize() const
{
    return m_histogramSize;
}

medIntParameter *animaSymmetryPlaneProcess::pyramidLevelsNumber() const
{
    return m_pyramidLevelsNumber;
}

medDoubleParameter *animaSymmetryPlaneProcess::upperBoundAngle() const
{
    return m_upperBoundAngle;
}

medDoubleParameter *animaSymmetryPlaneProcess::upperBoundDistance() const
{
    return m_upperBoundDistance;
}

void animaSymmetryPlaneProcess::setMetric(int value)
{
    m_Metric = value;
}

QString animaSymmetryPlaneProcess::caption() const
{
    return "Symmetry plane image alignment";
}

QString animaSymmetryPlaneProcess::description() const
{
    return "Realign image on its symmetry plane";
}

medAbstractJob::medJobExitStatus animaSymmetryPlaneProcess::run()
{
    if (!this->input())
    {
        qDebug() << "No input, aborting symmetry plane alignment";
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    QString type = this->input()->identifier();
    unsigned int nbDimension =(*(type.end() - 1)).digitValue();

    if (nbDimension != 3)
        return medAbstractJob::MED_JOB_EXIT_FAILURE;

    medAbstractImageData *out = qobject_cast <medAbstractImageData *> (medAbstractDataFactory::instance()->create("itkDataImageFloat3"));
    this->setOutput(out);

    if (type.contains("itkDataImageChar"))
    {
        return this->_run<char>();
    }
    else if (type.contains("itkDataImageUChar"))
    {
        return this->_run<unsigned char>();
    }
    else if (type.contains("itkDataImageShort"))
    {
        return this->_run<short>();
    }
    else if (type.contains("itkDataImageUShort"))
    {
        return this->_run<unsigned short>();
    }
    else if (type.contains("itkDataImageInt"))
    {
        return this->_run<int>();
    }
    else if (type.contains("itkDataImageUInt"))
    {
        return this->_run<unsigned int>();
    }
    else if (type.contains("itkDataImageLong"))
    {
        return this->_run<long>();
    }
    else if (type.contains("itkDataImageULong"))
    {
        return this->_run<unsigned long>();
    }
    else if (type.contains("itkDataImageFloat"))
    {
        return this->_run<float>();
    }
    else if (type.contains("itkDataImageDouble"))
    {
        return this->_run<double>();
    }

    return medAbstractJob::MED_JOB_EXIT_FAILURE;
}

template <class PixelType>
medAbstractJob::medJobExitStatus animaSymmetryPlaneProcess::_run()
{
    typedef itk::Image <PixelType,3> InputImageType;
    typedef anima::PyramidalSymmetryBridge <PixelType, double> PyramidSymType;

    typename PyramidSymType::Pointer matcher = PyramidSymType::New();

    // set parameters
    matcher->SetMetric((Metric)m_Metric);
    matcher->SetOptimizerMaxIterations(m_optimizerMaximumIterations->value());
    matcher->SetHistogramSize(m_histogramSize->value());
    matcher->SetUpperBoundAngle(m_upperBoundAngle->value());
    matcher->SetUpperBoundDistance(m_upperBoundDistance->value());
    matcher->SetNumberOfPyramidLevels(m_pyramidLevelsNumber->value());
    matcher->SetNumberOfWorkUnits(itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads());

    InputImageType *inputObject = dynamic_cast<InputImageType *> ((itk::Object *)this->input()->data());

    // set images
    matcher->SetReferenceImage(inputObject);
    matcher->SetFloatingImage(inputObject);

    m_symmetryplanebridge = matcher;

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaSymmetryPlaneProcess::eventCallback);

    m_symmetryplanebridge->AddObserver(itk::ProgressEvent(), callback);

    // process image
    try
    {
        m_symmetryplanebridge->Update();
    }
    catch(itk::ProcessAborted &e)
    {
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    // retrieve results (images and transforms)
    medAbstractImageData *out = this->output();
    out->setData(matcher->GetOutputImage());

    m_outputRealignTransform = matcher->GetOutputRealignTransform();

    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

animaSymmetryPlaneProcess::TransformPointer &animaSymmetryPlaneProcess::outputRealignTransform()
{
    return m_outputRealignTransform;
}

void animaSymmetryPlaneProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_symmetryplanebridge.IsNotNull())
            m_symmetryplanebridge->AbortGenerateDataOn();
    }
}
