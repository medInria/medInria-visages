#pragma once

#include <dtkCoreSupport/dtkPlugin.h>

#include "animaPyramidalBMRegistrationPluginExport.h"

class ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_EXPORT animaPyramidalBMRegistrationPluginPrivate;

class ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_EXPORT animaPyramidalBMRegistrationPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "fr.inria.animaPyramidalBMRegistrationPlugin" FILE "animaPyramidalBMRegistrationPlugin.json")
    Q_INTERFACES(dtkPlugin)
    
public:
    animaPyramidalBMRegistrationPlugin(QObject *parent = 0);
    ~animaPyramidalBMRegistrationPlugin(void);
    
    virtual bool initialize(void);
    virtual bool uninitialize(void);
    
    virtual QString name(void) const;
    virtual QString identifier(void) const;
    virtual QString description(void) const;
    virtual QString contact(void) const;
    virtual QString version (void) const;
    virtual QStringList authors(void) const;
    virtual QStringList contributors(void) const;
    virtual QStringList dependencies(void) const;
    
    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;
    
private:
    animaPyramidalBMRegistrationPluginPrivate *d;
};
