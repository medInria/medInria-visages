#pragma once

#include <animaDataMCMImageWriterBase.h>
#include <animaDataMCMImagePluginExport.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaNiftiDataMCMImageWriter : public animaDataMCMImageWriterBase
{
    Q_OBJECT

public:
    animaNiftiDataMCMImageWriter();
    virtual ~animaNiftiDataMCMImageWriter();

    virtual QString identifier()  const;
    virtual QString description() const;

    static bool registered();

    static dtkAbstractDataWriter* create();
};
