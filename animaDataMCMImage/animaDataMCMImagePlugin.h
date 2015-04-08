#pragma once

#include <dtkCore/dtkPlugin.h>
#include <animaDataMCMImagePluginExport.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImagePluginPrivate;

class ANIMADATAMCMIMAGEPLUGIN_EXPORT animaDataMCMImagePlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     animaDataMCMImagePlugin(QObject *parent = 0);
    ~animaDataMCMImagePlugin();

    virtual bool initialize();
    virtual bool uninitialize();

    virtual QString name() const;
    virtual QString description() const;

    virtual QStringList tags() const;
    virtual QStringList types() const;

    virtual QString version() const;
    virtual QString contact(void) const;
    virtual QStringList authors() const;
    virtual QStringList contributors() const;

private:
     animaDataMCMImagePluginPrivate *d;
};
