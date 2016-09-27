#include <animaDataMCMImageReader.h>

#include <animaMCMPrivateFileReader.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <animaDataMCMImageFloat3.h>
#include <animaDataMCMImageDouble3.h>

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
    return s_handled();
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
    return "Reader for MCM images";
}

bool animaDataMCMImageReader::canRead (const QStringList &paths)
{
    if (paths.count())
        return this->canRead (paths[0]);
    return false;
}

bool animaDataMCMImageReader::canRead (const QString &path)
{
    if (path.endsWith(".mcm"))
        return true;

    return false;
}

bool animaDataMCMImageReader::readInformation (const QStringList &paths)
{
    if (paths.count())
        return this->readInformation (paths[0]);

    return false;
}

bool animaDataMCMImageReader::readInformation (const QString &path)
{
    itk::ImageIOBase::IOComponentType componentType = anima::GetMCMComponentType(path.toStdString());
    
    medAbstractData* medData = dynamic_cast<medAbstractData*>(this->data());

    if (!medData)
    {
        switch (componentType)
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
            qDebug() << "Unsupported component type in MCM readInformation";
            return false ;
        }
    }

    if (medData)
        medData->addMetaData ("FilePath", QStringList() << path);

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
            anima::MCMPrivateFileReader <double, 3> mcmReader;
            mcmReader.SetFileName(path.toStdString());

            try
            {
                mcmReader.Update();
            }
            catch (itk::ExceptionObject &e)
            {
                qDebug() << e.GetDescription();
                return false;
            }

            medData->setData (mcmReader.GetModelVectorImage());
        }
        else if (medData->identifier()=="animaDataMCMImageFloat3")
        {
            anima::MCMPrivateFileReader <float, 3> mcmReader;
            mcmReader.SetFileName(path.toStdString());

            try
            {
                mcmReader.Update();
            }
            catch (itk::ExceptionObject &e)
            {
                qDebug() << e.GetDescription();
                return false;
            }

            medData->setData (mcmReader.GetModelVectorImage());
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
