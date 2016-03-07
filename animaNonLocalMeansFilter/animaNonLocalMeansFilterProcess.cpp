#include <animaNonLocalMeansFilterProcess.h>

#include <medAbstractDataFactory.h>
#include <medAbstractImageData.h>
#include <itkCommand.h>

#include <animaNonLocalMeansImageFilter.h>
#include <animaNonLocalMeansTemporalImageFilter.h>

animaNonLocalMeansFilterProcess::animaNonLocalMeansFilterProcess(QObject *parent)
    : medAbstractImageDenoisingProcess(parent)
{
    m_denoisingfilter = 0;

    m_PatchHalfSize = new medIntParameter("patch_half_size", this);
    m_PatchHalfSize->setCaption("Patch half size");
    m_PatchHalfSize->setDescription("Patch half size");
    m_PatchHalfSize->setRange(1,10);
    m_PatchHalfSize->setValue(1);

    m_SearchNeighborhood = new medIntParameter("search_neighborhood", this);
    m_SearchNeighborhood->setCaption("Patch search neighborhood");
    m_SearchNeighborhood->setDescription("Patch search neighborhood");
    m_SearchNeighborhood->setRange(1,20);
    m_SearchNeighborhood->setValue(1);

    m_SearchStepSize = new medIntParameter("search_step_size", this);
    m_SearchStepSize->setCaption("Patch search step size");
    m_SearchStepSize->setDescription("Patch search step size");
    m_SearchStepSize->setRange(1,10);
    m_SearchStepSize->setValue(1);

    m_WeightThreshold = new medDoubleParameter("weight_threshold", this);
    m_WeightThreshold->setCaption("NL weight threshold");
    m_WeightThreshold->setDescription("NL weight threshold");
    m_WeightThreshold->setRange(0.0,1.0);
    m_WeightThreshold->setValue(0.0);

    m_BetaParameter = new medDoubleParameter("beta_parameter", this);
    m_BetaParameter->setCaption("Beta for local noise estimation");
    m_BetaParameter->setDescription("Beta for local noise estimation");
    m_BetaParameter->setValue(1.0);

    m_MeanMinThreshold = new medDoubleParameter("mean_min_threshold", this);
    m_MeanMinThreshold->setCaption("Means threshold min");
    m_MeanMinThreshold->setDescription("Means threshold minimal value");
    m_MeanMinThreshold->setValue(0.95);

    m_VarMinThreshold = new medDoubleParameter("var_min_threshold", this);
    m_VarMinThreshold->setCaption("Variance threshold min");
    m_VarMinThreshold->setDescription("Variance threshold minimal value");
    m_VarMinThreshold->setValue(0.5);

    // For noise assumption
    m_WeightedMethod = 0;

    m_TemporalImage = new medBoolParameter("temporal_image",this);
    m_TemporalImage->setCaption("Image with a temporal dimension");
    m_TemporalImage->setDescription("Does the image have a temporal dimension?");
    m_TemporalImage->setValue(false);
}

animaNonLocalMeansFilterProcess::~animaNonLocalMeansFilterProcess()
{

}

medIntParameter *animaNonLocalMeansFilterProcess::patchHalfSize() const
{
    return m_PatchHalfSize;
}

medIntParameter *animaNonLocalMeansFilterProcess::searchNeighborhood() const
{
    return m_SearchNeighborhood;
}

medIntParameter *animaNonLocalMeansFilterProcess::searchStepSize() const
{
    return m_SearchStepSize;
}

medDoubleParameter *animaNonLocalMeansFilterProcess::weightThreshold() const
{
    return m_WeightThreshold;
}

medDoubleParameter *animaNonLocalMeansFilterProcess::betaParameter() const
{
    return m_BetaParameter;
}

medDoubleParameter *animaNonLocalMeansFilterProcess::meanMinThreshold() const
{
    return m_MeanMinThreshold;
}

medDoubleParameter *animaNonLocalMeansFilterProcess::varMinThreshold() const
{
    return m_VarMinThreshold;
}

medBoolParameter *animaNonLocalMeansFilterProcess::temporalImage() const
{
    return m_TemporalImage;
}

int animaNonLocalMeansFilterProcess::weightMethod() const
{
    return m_WeightedMethod;
}

void animaNonLocalMeansFilterProcess::setWeightedMethod(int value)
{
    m_WeightedMethod = value;
}

QString animaNonLocalMeansFilterProcess::caption() const
{
    return "Non-local means denoising";
}

QString animaNonLocalMeansFilterProcess::description() const
{
    return "Perform non-local means denoising of an image";
}

medAbstractJob::medJobExitStatus animaNonLocalMeansFilterProcess::run()
{
    QString type = this->input()->identifier();
    unsigned int nbDimension =(*(type.end() - 1)).digitValue();

    medAbstractImageData *out = qobject_cast <medAbstractImageData *> (medAbstractDataFactory::instance()->create(type));
    this->setOutput(out);

    if ( type.contains("itkDataImageChar"))
    {
        return switchDimension<char>(nbDimension);
    }
    else if (type.contains("itkDataImageUChar"))
    {
        return switchDimension<unsigned char>(nbDimension);
    }
    else if (type.contains("itkDataImageShort"))
    {
        return switchDimension<short>(nbDimension);
    }
    else if (type.contains("itkDataImageUShort"))
    {
        return switchDimension<unsigned short>(nbDimension);
    }
    else if (type.contains("itkDataImageInt"))
    {
        return switchDimension<int>(nbDimension);
    }
    else if (type.contains("itkDataImageUInt"))
    {
        return switchDimension<unsigned int>(nbDimension);
    }
    else if (type.contains("itkDataImageLong"))
    {
        return switchDimension<long>(nbDimension);
    }
    else if (type.contains("itkDataImageULong"))
    {
        return switchDimension<unsigned long>(nbDimension);
    }
    else if (type.contains("itkDataImageFloat"))
    {
        return switchDimension<float>(nbDimension);
    }
    else if (type.contains("itkDataImageDouble"))
    {
        return switchDimension<double>(nbDimension);
    }

    return medAbstractJob::MED_JOB_EXIT_FAILURE;
}

template <class PixelType>
medAbstractJob::medJobExitStatus
animaNonLocalMeansFilterProcess::switchDimension(unsigned int const nbDimension)
{
    switch(nbDimension)
    {
        case 2:
            return switchTemporal<itk::Image<PixelType, 2> >();

        case 3:
            return switchTemporal<itk::Image<PixelType, 3> >();

        case 4:
            return switchTemporal<itk::Image<PixelType, 4> >();
    }

    return medAbstractJob::MED_JOB_EXIT_FAILURE;
}

template <class ImageType>
medAbstractJob::medJobExitStatus
animaNonLocalMeansFilterProcess::switchTemporal()
{
    if (!m_TemporalImage->value())
        return updateNLMeans<ImageType>();

    return updateNLMeansTemporal<ImageType>();
}

template <class ImageType>
medAbstractJob::medJobExitStatus
animaNonLocalMeansFilterProcess::updateNLMeans()
{
    typedef anima::NonLocalMeansImageFilter <ImageType> FilterType;
    typename FilterType::Pointer filter = FilterType::New();

    filter->SetPatchHalfSize(m_PatchHalfSize->value());
    filter->SetSearchStepSize(m_SearchStepSize->value());
    filter->SetSearchNeighborhood(m_SearchNeighborhood->value());
    filter->SetWeightThreshold(m_WeightThreshold->value());
    filter->SetBetaParameter(m_BetaParameter->value());
    filter->SetMeanMinThreshold(m_MeanMinThreshold->value());
    filter->SetVarMinThreshold(m_VarMinThreshold->value());

    if (!m_WeightedMethod)
        filter->SetWeightMethod(FilterType::EXP);
    else
        filter->SetWeightMethod(FilterType::RICIAN);

    filter->SetInput(dynamic_cast<ImageType*>((itk::Object*)(this->input()->data())));

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaNonLocalMeansFilterProcess::eventCallback);

    filter->AddObserver(itk::ProgressEvent(), callback);

    m_denoisingfilter = filter;

    try
    {
        m_denoisingfilter->Update();
    }
    catch(itk::ProcessAborted &e)
    {
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    medAbstractImageData *out = this->output();
    out->setData(filter->GetOutput());

    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

template <class ImageType>
medAbstractJob::medJobExitStatus
animaNonLocalMeansFilterProcess::updateNLMeansTemporal()
{
    typedef anima::NonLocalMeansTemporalImageFilter<ImageType> FilterType;
    typename FilterType::Pointer filter = FilterType::New();

    filter->SetPatchHalfSize(m_PatchHalfSize->value());
    filter->SetSearchStepSize(m_SearchStepSize->value());
    filter->SetSearchNeighborhood(m_SearchNeighborhood->value());
    filter->SetWeightThreshold(m_WeightThreshold->value());
    filter->SetBetaParameter(m_BetaParameter->value());
    filter->SetMeanMinThreshold(m_MeanMinThreshold->value());
    filter->SetVarMinThreshold(m_VarMinThreshold->value());

    if (!m_WeightedMethod)
        filter->SetWeightMethod(FilterType::EXP);
    else
        filter->SetWeightMethod(FilterType::RICIAN);

    filter->SetInput(dynamic_cast<ImageType*>((itk::Object*)(this->input()->data())));

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaNonLocalMeansFilterProcess::eventCallback);

    filter->AddObserver(itk::ProgressEvent(), callback);

    m_denoisingfilter = filter;

    try
    {
        m_denoisingfilter->Update();
    }
    catch(itk::ProcessAborted &e)
    {
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    medAbstractImageData *out = this->output();
    out->setData(filter->GetOutput());

    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

void animaNonLocalMeansFilterProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_denoisingfilter.IsNotNull())
            m_denoisingfilter->AbortGenerateDataOn();
    }
}
