#pragma once

#include <medAbstractRelaxometryEstimationProcess.h>
#include <animaRelaxometryPluginExport.h>

class ANIMARELAXOMETRYPLUGIN_EXPORT animaRelaxometryPlugin : public medAbstractSingleFilterOperationProcessPlugin
{
    Q_OBJECT
    Q_INTERFACES(medAbstractSingleFilterOperationProcessPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.animaRelaxometryPlugin" FILE "animaRelaxometryPlugin.json")

public:
    animaRelaxometryPlugin() {}
    virtual ~animaRelaxometryPlugin() {}
    
    virtual void initialize();
    virtual void uninitialize();
};


