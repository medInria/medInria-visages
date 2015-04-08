#pragma once

#include <dtkCore/dtkAbstractDataWriter.h>

#include <animaDataMCMImagePluginExport.h>
#include <itkImageIOBase.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageWriterBase : public dtkAbstractDataWriter
{
    Q_OBJECT

public:
    animaDataMCMImageWriterBase();
    virtual ~animaDataMCMImageWriterBase();

    virtual QStringList handled() const;

    virtual QStringList supportedFileExtensions() const;

public slots:
    bool write    (const QString& path);
    bool canWrite (const QString& path);

private:
    template <class PixelType> bool write(const QString& path, PixelType dummyArgument);

protected:
    static QStringList s_handled();

    itk::ImageIOBase::Pointer io;
};
