#pragma once

#include <medAbstractImageDenoisingProcess.h>
#include "animaNonLocalMeansFilterPluginExport.h"

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterPlugin : public medAbstractSingleFilterOperationProcessPlugin
{
    Q_OBJECT
    Q_INTERFACES(medAbstractSingleFilterOperationProcessPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.animaNonLocalMeansFilterPlugin" FILE "animaNonLocalMeansFilterPlugin.json")

public:
    animaNonLocalMeansFilterPlugin() {}
    virtual ~animaNonLocalMeansFilterPlugin() {}

    virtual void initialize();
    virtual void uninitialize();
};
