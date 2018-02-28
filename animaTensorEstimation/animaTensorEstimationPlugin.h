#pragma once

#include <medAbstractDiffusionModelEstimationProcess.h>
#include <animaTensorEstimationPluginExport.h>

class ANIMATENSORESTIMATIONPLUGIN_EXPORT animaTensorEstimationPlugin : public medAbstractDiffusionModelEstimationProcessPlugin
{
    Q_OBJECT

    Q_INTERFACES(medAbstractDiffusionModelEstimationProcessPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.animaTensorEstimationPlugin" FILE "animaTensorEstimationPlugin.json")

public:
     animaTensorEstimationPlugin() {}
     virtual ~animaTensorEstimationPlugin() {}

public:
    void initialize();
    void uninitialize();
};
