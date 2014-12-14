#include <animaMetaDataMCMImageWriter.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <itkMetaImageIO.h>

static QString s_identifier()
{
    return "animaMetaDataMCMImageWriter";
}

animaMetaDataMCMImageWriter::animaMetaDataMCMImageWriter(): animaDataMCMImageWriterBase()
{
    this->io = itk::MetaImageIO::New();
}

animaMetaDataMCMImageWriter::~animaMetaDataMCMImageWriter()
{

}

bool animaMetaDataMCMImageWriter::registered()
{
  return medAbstractDataFactory::instance()->registerDataWriterType(s_identifier(), animaDataMCMImageWriterBase::s_handled(),
                                                                    create);
}


QString animaMetaDataMCMImageWriter::description() const
{
    return tr("Anima MetaData MCM Image exporter");
}

QString animaMetaDataMCMImageWriter::identifier() const
{
    return s_identifier();
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter * animaMetaDataMCMImageWriter::create()
{
    return new animaMetaDataMCMImageWriter();
}
