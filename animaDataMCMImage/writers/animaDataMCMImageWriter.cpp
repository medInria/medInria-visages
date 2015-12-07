#include <animaDataMCMImageWriter.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <animaMCMFileWriter.h>

#include <animaDataMCMImageFloat3.h>
#include <animaDataMCMImageDouble3.h>

#include <animaMCMImage.h>

QStringList animaDataMCMImageWriter::s_handled()
{
    return QStringList() << "animaDataMCMImageDouble3"
                         << "animaDataMCMImageFloat3";
}

animaDataMCMImageWriter::animaDataMCMImageWriter(): dtkAbstractDataWriter()
{
}

animaDataMCMImageWriter::~animaDataMCMImageWriter()
{

}

QStringList animaDataMCMImageWriter::handled() const
{
    return s_handled();
}

QString animaDataMCMImageWriter::identifier() const
{
    return "animaDataMCMImageWriter";
}

QString animaDataMCMImageWriter::description() const
{
    return "Writer for MCM images";
}


bool animaDataMCMImageWriter::registered()
{
  return medAbstractDataFactory::instance()->registerDataWriterType("animaDataMCMImageWriter", s_handled(),
                                                                    createAnimaDataMCMImageWriter);
}

QStringList animaDataMCMImageWriter::supportedFileExtensions() const
{
    QStringList ret;
    ret << ".mcm";

    return ret;
}

bool animaDataMCMImageWriter::canWrite(const QString& path)
{
    if (path.endsWith(".mcm"))
        return true;

    return false;
}

bool animaDataMCMImageWriter::write(const QString& path)
{
    if (!this->data())
        return false;

    if (medAbstractData *medData = dynamic_cast<medAbstractData*>(this->data()) )
    {
        if(medData->identifier()=="animaDataMCMImageFloat3")
        {
            float dummy = 0;
            write(path, dummy);
        }

        else if(medData->identifier()=="animaDataMCMImageDouble3")
        {

            double dummy = 0;
            write(path, dummy);
        }

        else
        {
            qWarning() << "Unrecognized pixel type";
            return false;
        }
    }

    return true;
}

template <class PixelType>
bool animaDataMCMImageWriter::write(const QString& path, PixelType dummyArgument)
{
    anima::MCMFileWriter <PixelType, 3> mcmWriter;
    mcmWriter.SetFileName(path.toStdString());

    typedef typename anima::MCMImage<PixelType, 3> MCMImageType;
    typedef typename MCMImageType::Pointer MCMImageTypePointer;
    MCMImageTypePointer image = dynamic_cast<MCMImageType *> ((itk::Object*)(this->data()->output()));

    mcmWriter.SetInputImage(image);

    try
    {
        mcmWriter.Update();
    }
    catch(itk::ExceptionObject &e)
    {
        qDebug() << e.GetDescription();
        return false;
    }

    return true;
}

dtkAbstractDataWriter *createAnimaDataMCMImageWriter()
{
    return new animaDataMCMImageWriter;
}
