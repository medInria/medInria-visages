#pragma once

#include <animaDataMCMImageWriterBase.h>
#include <animaDataMCMImagePluginExport.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaMetaDataMCMImageWriter : public animaDataMCMImageWriterBase
{
    Q_OBJECT

public:
    animaMetaDataMCMImageWriter();
    virtual ~animaMetaDataMCMImageWriter();

    virtual QString identifier()  const;
    virtual QString description() const;

    static bool registered();

    static dtkAbstractDataWriter* create();
};
