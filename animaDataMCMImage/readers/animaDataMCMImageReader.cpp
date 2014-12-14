#include <animaDataMCMImageReader.h>

#include <animaDDIDistribution.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <itkImageFileReader.h>
#include <itkObjectFactoryBase.h>
#include <itkImageRegionConstIteratorWithIndex.h>
#include <itkImageRegionIteratorWithIndex.h>

// /////////////////////////////////////////////////////////////////
// animaDataMCMImageReader
// /////////////////////////////////////////////////////////////////

animaDataMCMImageReader::animaDataMCMImageReader() : dtkAbstractDataReader()
{
}

animaDataMCMImageReader::~animaDataMCMImageReader()
{
}

QStringList animaDataMCMImageReader::handled() const
{
    return QStringList() << "animaDataMCMImageDouble3"
                         << "animaDataMCMImageFloat3";
}

QStringList animaDataMCMImageReader::s_handled()
{
    return QStringList() << "animaDataMCMImageDouble3"
                         << "animaDataMCMImageFloat3";
}

bool animaDataMCMImageReader::registered()
{
  return medAbstractDataFactory::instance()->registerDataReaderType("animaDataMCMImageReader", s_handled(),
                                                                    createAnimaDataMCMImageReader);
}

QString animaDataMCMImageReader::identifier() const
{
    return "animaDataMCMImageReader";
}

QString animaDataMCMImageReader::description() const
{
    return "Reader for Anima MCM images";
}

bool animaDataMCMImageReader::canRead (const QStringList &paths)
{
    if (paths.count())
        return this->canRead (paths[0]);
    return false;
}

bool animaDataMCMImageReader::canRead (const QString &path)
{
    // TO DO : add part to read initial XML file and see if it's conform after

    itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO(path.toAscii().constData(),
                                                                           itk::ImageIOFactory::ReadMode);

    imageIO->SetFileName(path.toAscii().constData());
    try
    {
        imageIO->ReadImageInformation();
    }
    catch (itk::ExceptionObject &e)
    {
        qDebug() << e.GetDescription();
        return false;
    }

    if ((imageIO->GetNumberOfComponents() - 4) % anima::CompartmentSize != 0)
        return false;

    return true;
}

bool animaDataMCMImageReader::readInformation (const QStringList &paths)
{
    if (paths.count())
        return this->readInformation (paths[0]);

    return false;
}

bool animaDataMCMImageReader::readInformation (const QString &path)
{
    // TO DO : add part to read initial XML file and see if it's conform after

    itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO(path.toAscii().constData(),
                                                                           itk::ImageIOFactory::ReadMode);

    imageIO->SetFileName(path.toAscii().constData());
    try
    {
        imageIO->ReadImageInformation();
    }
    catch (itk::ExceptionObject &e)
    {
        qDebug() << e.GetDescription();
        return false;
    }
    
    medAbstractData* medData = dynamic_cast<medAbstractData*>(this->data());

    if (!medData)
    {
        switch (imageIO->GetComponentType())
        {
        case itk::ImageIOBase::FLOAT:
            medData = medAbstractDataFactory::instance()->create ("animaDataMCMImageFloat3");
            if (medData)
                this->setData ( medData );
            break;

        case itk::ImageIOBase::DOUBLE:
            medData = medAbstractDataFactory::instance()->create ("animaDataMCMImageDouble3");
            if (medData)
                this->setData ( medData );
            break;

        default:
            qDebug() << "Unsupported component type";
            return false ;
        }
    }

    if (medData)
    {
        medData->addMetaData ("FilePath", QStringList() << path);
    }

    return true;
}

bool animaDataMCMImageReader::read (const QStringList &paths)
{
    if (paths.count())
        return this->read (paths[0]);
    return false;
}

bool animaDataMCMImageReader::read (const QString &path)
{
    qDebug() << "Read with: " << this->description();

    this->readInformation(path);

    if (medAbstractData *medData = dynamic_cast<medAbstractData*>(this->data()))
    {
        if (medData->identifier() == "animaDataMCMImageDouble3")
        {
            typedef itk::VectorImage<double, 3> MCMImageType;

            typedef itk::ImageFileReader<MCMImageType> ReaderType;

            MCMImageType::Pointer image = 0;

            ReaderType::Pointer reader = ReaderType::New();
            reader->SetFileName ( path.toAscii().constData() );
            try
            {
                reader->Update();
            }
            catch (itk::ExceptionObject &e)
            {
                qDebug() << e.GetDescription();
                return false;
            }
            image = reader->GetOutput();
            medData->setData (image);
        }
        else if (medData->identifier()=="animaDataMCMImageFloat3")
        {
            typedef itk::VectorImage<float, 3> MCMImageType;

            typedef itk::ImageFileReader<MCMImageType> ReaderType;

            MCMImageType::Pointer image = 0;

            ReaderType::Pointer reader = ReaderType::New();
            reader->SetFileName ( path.toAscii().constData() );
            try
            {
                reader->Update();
            }
            catch (itk::ExceptionObject &e)
            {
                qDebug() << e.GetDescription();
                return false;
            }
            image = reader->GetOutput();
            medData->setData (image);

        }
        else
        {
            qDebug() << "Unsupported data type";
            return false;
        }
    }
    else
    {
        qDebug() << "No data set or could not create one";
        return false;
    }

    return true;
}

dtkAbstractDataReader *createAnimaDataMCMImageReader()
{
    return new animaDataMCMImageReader;
}
