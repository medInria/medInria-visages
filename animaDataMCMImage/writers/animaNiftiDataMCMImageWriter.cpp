#include <animaNiftiDataMCMImageWriter.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <itkNiftiImageIO.h>

static QString s_identifier()
{
    return "animaNiftiDataMCMImageWriter";
}

animaNiftiDataMCMImageWriter::animaNiftiDataMCMImageWriter(): animaDataMCMImageWriterBase()
{
    this->io = itk::NiftiImageIO::New();
}

animaNiftiDataMCMImageWriter::~animaNiftiDataMCMImageWriter()
{

}

bool animaNiftiDataMCMImageWriter::registered()
{
  return medAbstractDataFactory::instance()->registerDataWriterType(s_identifier(), animaDataMCMImageWriterBase::s_handled(),
                                                                    create);
}


QString animaNiftiDataMCMImageWriter::description() const
{
    return tr("Anima Nifti MCM Image exporter");
}

QString animaNiftiDataMCMImageWriter::identifier() const
{
    return s_identifier();
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter * animaNiftiDataMCMImageWriter::create()
{
    return new animaNiftiDataMCMImageWriter();
}
