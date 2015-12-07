#pragma once

#include <medAbstractDiffusionModelEstimationProcess.h>
#include <animaMCMEstimationPluginExport.h>

class ANIMAMCMESTIMATIONPLUGIN_EXPORT animaMCMEstimationPlugin : public medAbstractDiffusionModelEstimationProcessPlugin
{
    Q_OBJECT

    Q_INTERFACES(medAbstractDiffusionModelEstimationProcessPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.animaMCMEstimationPlugin" FILE "animaMCMEstimationPlugin.json")

public:
     animaMCMEstimationPlugin() {}
     virtual ~animaMCMEstimationPlugin() {}

public:
    void initialize();
    void uninitialize();
};
