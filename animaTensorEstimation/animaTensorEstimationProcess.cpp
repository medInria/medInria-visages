#include <animaTensorEstimationProcess.h>

#include <medAbstractImageData.h>
#include <medAbstractDiffusionModelImageData.h>
#include <medAbstractDataFactory.h>

#include <animaDTIEstimationImageFilter.h>
#include <animaReadWriteFunctions.h>

#include <itkTensor.h>
#include <itkImage.h>
#include <itkImageRegionIterator.h>

animaTensorEstimationProcess::animaTensorEstimationProcess(QObject *parent)
    : medAbstractDiffusionModelEstimationProcess(parent)
{
    m_estimationfilter = 0;
}

animaTensorEstimationProcess::~animaTensorEstimationProcess()
{
}

QString animaTensorEstimationProcess::caption() const
{
    return "Tensor estimation";
}

QString animaTensorEstimationProcess::description() const
{
    return "Use Anima to estimate tensors from DWI data (constrained to be SPD and multi-shell compatible)";
}

medAbstractJob::medJobExitStatus animaTensorEstimationProcess::run()
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
medAbstractJob::medJobExitStatus animaTensorEstimationProcess::_run()
{
    typedef itk::Image <inputType,4> DWIImageType;
    typedef itk::Image <inputType,3> SingleDWIImageType;
    typename DWIImageType::Pointer inData = dynamic_cast<DWIImageType *>((itk::Object*)(this->input()->data()));

    if (!inData)
    {
        qDebug() << "No input data to tensor estimation";
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    typedef anima::DTIEstimationImageFilter <inputType,float> FilterType;

    typename FilterType::Pointer filter;
    filter = FilterType::New();

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData((void*)this);
    callback->SetCallback(animaTensorEstimationProcess::eventCallback);

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

    filter->SetBValuesList(bValsList);
    filter->SetB0Threshold(1);

    m_estimationfilter = filter;

    try
    {
        m_estimationfilter->Update();
    }
    catch(itk::ExceptionObject &e)
    {
        qDebug() << "Error in tensor estimation process" << e.GetDescription();
        return medAbstractJob::MED_JOB_EXIT_FAILURE;
    }

    medAbstractDiffusionModelImageData *out;
    out = qobject_cast<medAbstractDiffusionModelImageData *>(medAbstractDataFactory::instance()->create("itkDataTensorImageFloat3"));

    typedef itk::Tensor <float, 3> TensorType;
    typedef itk::Image <TensorType, 3> TensorImageType;

    TensorImageType::Pointer outputTTKImage = TensorImageType::New();
    outputTTKImage->Initialize();
    outputTTKImage->SetRegions(filter->GetOutput()->GetLargestPossibleRegion());
    outputTTKImage->SetSpacing (filter->GetOutput()->GetSpacing());
    outputTTKImage->SetOrigin (filter->GetOutput()->GetOrigin());
    outputTTKImage->SetDirection (filter->GetOutput()->GetDirection());
    outputTTKImage->Allocate();

    typedef itk::ImageRegionIterator <typename FilterType::OutputImageType> VectorIteratorType;
    typedef itk::ImageRegionIterator <TensorImageType> TensorImageIteratorType;

    TensorImageIteratorType outItr(outputTTKImage, outputTTKImage->GetLargestPossibleRegion());
    VectorIteratorType vectorItr(filter->GetOutput(), outputTTKImage->GetLargestPossibleRegion());

    typename FilterType::OutputImageType::PixelType outVector;
    TensorType tmpTensor;
    while (!vectorItr.IsAtEnd())
    {
        outVector = vectorItr.Get();

        for (unsigned int i = 0;i < 6;++i)
            tmpTensor[i] = outVector[i];

        outItr.Set(tmpTensor);

        ++vectorItr;
        ++outItr;
    }

    out->setData(outputTTKImage);
    this->setOutput(out);
    return medAbstractJob::MED_JOB_EXIT_SUCCESS;
}

void animaTensorEstimationProcess::cancel()
{
    if(this->isRunning())
    {
        if (m_estimationfilter.IsNotNull())
            m_estimationfilter->AbortGenerateDataOn();
    }
}
