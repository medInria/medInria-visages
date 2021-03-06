#include <animaMCMEstimationProcess.h>

#include <medAbstractImageData.h>
#include <medAbstractDiffusionModelImageData.h>
#include <medAbstractDataFactory.h>

#include <animaPrivateMCMEstimatorImageFilter.h>

animaMCMEstimationProcess::animaMCMEstimationProcess(QObject *parent)
    : medAbstractDiffusionModelEstimationProcess(parent)
{
    m_estimationfilter = 0;

    m_compartmentType = anima::Tensor;

    m_nbFascicles = new medIntParameter("nb_fascicles", this);
    m_nbFascicles->setCaption("Number of fascicles");
    m_nbFascicles->setDescription("Number of individual fascicles in estimated MCM");
    m_nbFascicles->setRange(0,3);
    m_nbFascicles->setValue(1);

    m_freeWaterCompartment = new medBoolParameter("free_water_comp",this);
    m_freeWaterCompartment->setCaption("Free water compartment");
    m_freeWaterCompartment->setDescription("Estimated MCM with free water compartment");
    m_freeWaterCompartment->setValue(true);

    m_irWaterCompartment = new medBoolParameter("iso_restricted_water_comp",this);
    m_irWaterCompartment->setCaption("Isotropic restricted water compartment");
    m_irWaterCompartment->setDescription("Estimated MCM with IR water compartment");
    m_irWaterCompartment->setValue(true);

    m_stationaryWaterCompartment = new medBoolParameter("stationary_water_comp",this);
    m_stationaryWaterCompartment->setCaption("Stationary water compartment");
    m_stationaryWaterCompartment->setDescription("Estimated MCM with stationary water compartment");
    m_stationaryWaterCompartment->setValue(false);

    m_modelSelection = new medBoolParameter("model_selection",this);
    m_modelSelection->setCaption("Model selection");
    m_modelSelection->setDescription("Perform AIC based model selection (number of fascicles will be the maximal number of fascicles)");
    m_modelSelection->setValue(false);

    m_nbRandomRestarts = new medIntParameter("nb_rand_restarts");
    m_nbRandomRestarts->setCaption("Number of random restarts");
    m_nbRandomRestarts->setDescription("Number of whole optimization random restarts");
    m_nbRandomRestarts->setRange(0,50);
    m_nbRandomRestarts->setValue(4);

    m_fixWeights = new medBoolParameter("fix_weights",this);
    m_fixWeights->setCaption("Fixed compartment weights");
    m_fixWeights->setDescription("Fix compartment weights in estimation");
    m_fixWeights->setValue(false);

    m_fixDiff = new medBoolParameter("fix_diffs",this);
    m_fixDiff->setCaption("Fixed compartment diffusivities");
    m_fixDiff->setDescription("Fix compartment diffusivities in estimation");
    m_fixDiff->setValue(false);

    m_fixIsoDiffs = new medBoolParameter("fix_iso_diffs",this);
    m_fixIsoDiffs->setCaption("Fixed isotropic water diffusivities");
    m_fixIsoDiffs->setDescription("Fix isotropic water diffusivities in estimation");
    m_fixIsoDiffs->setValue(true);

    m_fixKappa = new medBoolParameter("fix_kappa",this);
    m_fixKappa->setCaption("Fixed compartment kappas");
    m_fixKappa->setDescription("Fix concentration in estimation (only for DDI)");
    m_fixKappa->setValue(false);

    m_fixEAF = new medBoolParameter("fix_eaf",this);
    m_fixEAF->setCaption("Fixed compartment EAF");
    m_fixEAF->setDescription("Fix extra-axonal fraction in estimation (only for DDI)");
    m_fixEAF->setValue(false);

    m_commonDiffusivities = new medBoolParameter("common_diffs",this);
    m_commonDiffusivities->setCaption("Common compartment diffusivities");
    m_commonDiffusivities->setDescription("Shared compartment diffusivities (one parameter for all compartments)");
    m_commonDiffusivities->setValue(false);

    m_commonKappa = new medBoolParameter("common_kappa",this);
    m_commonKappa->setCaption("Common compartment kappa");
    m_commonKappa->setDescription("Shared compartment concentrations (one parameter for all compartments, only for DDI)");
    m_commonKappa->setValue(false);

    m_commonEAF = new medBoolParameter("common_eaf",this);
    m_commonEAF->setCaption("Common compartment EAF");
    m_commonEAF->setDescription("Shared compartment extra-axonal fractions (one parameter for all compartments, only for DDI)");
    m_commonEAF->setValue(false);
}

animaMCMEstimationProcess::~animaMCMEstimationProcess()
{
}

QString animaMCMEstimationProcess::caption() const
{
    return "MCM estimation";
}

QString animaMCMEstimationProcess::description() const
{
    return "Use Anima to estimate multi-compartment models from DWI data";
}

medIntParameter *animaMCMEstimationProcess::nbFascicles() const
{
    return m_nbFascicles;
}

medBoolParameter *animaMCMEstimationProcess::freeWaterCompartment() const
{
    return m_freeWaterCompartment;
}

medBoolParameter *animaMCMEstimationProcess::irWaterCompartment() const
{
    return m_irWaterCompartment;
}

medBoolParameter *animaMCMEstimationProcess::stationaryWaterCompartment() const
{
    return m_stationaryWaterCompartment;
}

medBoolParameter *animaMCMEstimationProcess::modelSelection() const
{
    return m_modelSelection;
}

medIntParameter *animaMCMEstimationProcess::nbRandomRestarts() const
{
    return m_nbRandomRestarts;
}

medBoolParameter *animaMCMEstimationProcess::fixWeights() const
{
    return m_fixWeights;
}

medBoolParameter *animaMCMEstimationProcess::fixDiff() const
{
    return m_fixDiff;
}

medBoolParameter *animaMCMEstimationProcess::fixIsoDiffs() const
{
    return m_fixIsoDiffs;
}

medBoolParameter *animaMCMEstimationProcess::fixKappa() const
{
    return m_fixKappa;
}

medBoolParameter *animaMCMEstimationProcess::fixEAF() const
{
    return m_fixEAF;
}

medBoolParameter *animaMCMEstimationProcess::commonDiffusivities() const
{
    return m_commonDiffusivities;
}

medBoolParameter *animaMCMEstimationProcess::commonKappa() const
{
    return m_commonKappa;
}

medBoolParameter *animaMCMEstimationProcess::commonEAF() const
{
    return m_commonEAF;
}

medAbstractJob::medJobExitStatus animaMCMEstimationProcess::run()
{
    medAbstractJob::medJobExitStatus jobExitSatus = medAbstractJob::MED_JOB_EXIT_FAILURE;

    if(this->input())
    {
        this->extractGradientsFromInformation();
        QString id =  this->input()->identifier();

        if ( id == "itkDataImageChar4" )
        {
            jobExitSatus = this->_run<char>();
        }
        else if ( id == "itkDataImageUChar4" )
        {
            jobExitSatus = this->_run<unsigned char>();
        }
        else if ( id == "itkDataImageShort4" )
        {
            jobExitSatus = this->_run<short>();
        }
        else if ( id == "itkDataImageUShort4" )
        {
            jobExitSatus = this->_run<unsigned short>();
        }
        else if ( id == "itkDataImageInt4" )
        {
            jobExitSatus = this->_run<int>();
        }
        else if ( id == "itkDataImageUInt4" )
        {
            jobExitSatus = this->_run<unsigned int>();
        }
        else if ( id == "itkDataImageLong4" )
        {
            jobExitSatus = this->_run<long>();
        }
        else if ( id== "itkDataImageULong4" )
        {
            jobExitSatus = this->_run<unsigned long>();
        }
        if ( id == "itkDataImageFloat4" )
        {
            jobExitSatus = this->_run<float>();
        }
        else if ( id == "itkDataImageDouble4" )
        {
            jobExitSatus = this->_run<double>();
        }
    }

    return jobExitSatus;
}

template <class inputType>
medAbstractJob::medJobExitStatus animaMCMEstimationProcess::_run()
{
    typedef itk::Image <inputType,4> DWIImageType;
    typedef itk::Image <inputType,3> SingleDWIImageType;
    typename DWIImageType::Pointer inData = dynamic_cast<DWIImageType *>((itk::Object*)(this->input()->data()));

    if (!inData)
    {
        qDebug() << "No input data to MCM estimation";
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    typedef anima::PrivateMCMEstimatorImageFilter <inputType,float> DDIFilterType;
    typename DDIFilterType::Pointer filter = DDIFilterType::New();
    
    filter->SetUseConstrainedOrientationConcentration(m_fixKappa->value());
    if (!m_fixKappa->value())
        filter->SetUseCommonConcentrations(m_commonKappa->value());
    else
        filter->SetUseCommonConcentrations(false);
    
    filter->SetUseConstrainedExtraAxonalFraction(m_fixEAF->value());
    if (!m_fixEAF->value())
        filter->SetUseCommonExtraAxonalFractions(m_commonEAF->value());
    else
        filter->SetUseCommonExtraAxonalFractions(false);

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaMCMEstimationProcess::eventCallback);

    filter->AddObserver(itk::ProgressEvent(), callback);

    std::vector < itk::SmartPointer <SingleDWIImageType> > images = anima::getImagesFromHigherDimensionImage <DWIImageType,SingleDWIImageType> (inData);
    for (unsigned int i = 0;i < images.size();++i)
        filter->SetInput(i,images[i]);

    unsigned int gradientCount = this->gradients().size();
    vnl_vector_fixed <double,3> grad;

    for (unsigned int i = 0;i < gradientCount;++i)
    {
        for (unsigned int j = 0;j < 3;++j)
            grad[j] = this->gradients()[i][j];

        filter->AddGradientDirection(i,grad);
    }

    VectorType bValsList(gradientCount,1000);
    bValsList[0] = 0;
    if (this->bvalues().size() != 0)
        bValsList = this->bvalues();

    for (unsigned int i = 0;i < bValsList.size();++i)
        bValsList[i] = anima::GetGradientStrengthFromBValue(bValsList[i],anima::DiffusionSmallDelta, anima::DiffusionBigDelta);

    filter->SetGradientStrengths(bValsList);
    filter->SetB0Threshold(1);

    filter->SetModelWithFreeWaterComponent(m_freeWaterCompartment->value());
    filter->SetModelWithRestrictedWaterComponent(m_irWaterCompartment->value());
    filter->SetModelWithStationaryWaterComponent(m_stationaryWaterCompartment->value());

    filter->SetCompartmentType(m_compartmentType);
    filter->SetNumberOfCompartments(m_nbFascicles->value());
    filter->SetFindOptimalNumberOfCompartments(m_modelSelection->value());

    filter->SetMLEstimationStrategy(DDIFilterType::MaximumLikelihoodEstimationMode::VariableProjection);
    std::string optType = "levenberg";
    filter->SetOptimizer(optType);
    filter->SetAbsoluteCostChange(0.01);

    filter->SetUseConstrainedDiffusivity(m_fixDiff->value());
    filter->SetUseConstrainedFreeWaterDiffusivity(m_fixIsoDiffs->value());
    filter->SetUseConstrainedIRWDiffusivity(m_fixIsoDiffs->value());

    if (!m_fixDiff->value())
        filter->SetUseCommonDiffusivities(m_commonDiffusivities->value());
    else
        filter->SetUseCommonDiffusivities(false);

    m_estimationfilter = filter;

    try
    {
        m_estimationfilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        qDebug() << "Error in MCM estimation process" << e.GetDescription();
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    medAbstractDiffusionModelImageData *out;

    if (this->input()->identifier().contains("Double"))
        out = qobject_cast<medAbstractDiffusionModelImageData *>(medAbstractDataFactory::instance()->create("animaDataMCMImageDouble3"));
    else
        out = qobject_cast<medAbstractDiffusionModelImageData *>(medAbstractDataFactory::instance()->create("animaDataMCMImageFloat3"));

    out->setData(filter->GetOutput());
    this->setOutput(out);
    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

void animaMCMEstimationProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_estimationfilter.IsNotNull())
            m_estimationfilter->AbortGenerateDataOn();
    }
}
