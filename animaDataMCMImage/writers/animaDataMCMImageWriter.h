#pragma once

#include <dtkCore/dtkAbstractDataWriter.h>

#include <animaDataMCMImagePluginExport.h>
#include <animaMultiCompartmentModel.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImageWriter : public dtkAbstractDataWriter
{
    Q_OBJECT

public:
    animaDataMCMImageWriter();
    virtual ~animaDataMCMImageWriter();

    virtual QStringList handled() const;

    static QStringList s_handled();

    virtual QString identifier()  const;
    virtual QString description() const;

    virtual QStringList supportedFileExtensions() const;

    typedef anima::MultiCompartmentModel MCModelType;
    typedef MCModelType::Pointer MCModelPointer;

    static bool registered();

public slots:
    bool write    (const QString& path);
    bool canWrite (const QString& path);

private:
    template <class PixelType> bool write(const QString& path, PixelType dummyArgument, MCModelPointer &referenceModel);
};

dtkAbstractDataWriter *createAnimaDataMCMImageWriter();
