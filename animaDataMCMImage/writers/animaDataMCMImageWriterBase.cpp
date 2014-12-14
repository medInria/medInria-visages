#include <animaDataMCMImageWriterBase.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <itkImageFileWriter.h>
#include <itkImage.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkVectorImage.h>
#include <itkVector.h>


QStringList animaDataMCMImageWriterBase::s_handled()
{
    return QStringList() << "animaDataMCMImageDouble3"
                         << "animaDataMCMImageFloat3";
}

animaDataMCMImageWriterBase::animaDataMCMImageWriterBase(): dtkAbstractDataWriter()
{
    this->io = 0;
}

animaDataMCMImageWriterBase::~animaDataMCMImageWriterBase()
{

}

QStringList animaDataMCMImageWriterBase::handled() const
{
    return s_handled();
}

QStringList animaDataMCMImageWriterBase::supportedFileExtensions() const
{
    QStringList ret;

    if (this->io) {
        typedef itk::ImageIOBase::ArrayOfExtensionsType ArrayOfExtensionsType;
        const ArrayOfExtensionsType & extensions = this->io->GetSupportedWriteExtensions();
        for( ArrayOfExtensionsType::const_iterator it(extensions.begin());
             it != extensions.end(); ++it )
        {
            ret << it->c_str();
        }
    }
    return ret;
}

bool animaDataMCMImageWriterBase::canWrite(const QString& path)
{
    if (this->io.IsNull())
        return false;

    return this->io->CanWriteFile ( path.toAscii().constData() );
}

bool animaDataMCMImageWriterBase::write(const QString& path)
{
    if (!this->data())
        return false;

    if (this->io.IsNull())
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
bool animaDataMCMImageWriterBase::write(const QString& path, PixelType dummyArgument)
{
    typedef typename itk::VectorImage<PixelType, 3> MCMImageType;

    typedef typename MCMImageType::Pointer MCMImageTypePointer;
    MCMImageTypePointer image = dynamic_cast<MCMImageType *> ((itk::Object*)(this->data()->output()));

    typedef typename itk::ImageFileWriter<MCMImageType>::Pointer ImageFileWriterPointer;
    ImageFileWriterPointer myWriter = itk::ImageFileWriter<MCMImageType>::New();
    myWriter->SetFileName(path.toAscii().constData());
    myWriter->SetInput(image);

    try
    {
        myWriter->Write();
    }
    catch(itk::ExceptionObject &e)
    {
        qDebug() << e.GetDescription();
        return false;
    }

    return true;
}
