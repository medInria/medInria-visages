#pragma once

#include <medAbstractSymmetryPlaneAlignmentProcess.h>
#include "animaSymmetryPlanePluginExport.h"

class ANIMASYMMETRYPLANEPLUGIN_EXPORT animaSymmetryPlanePlugin : public medAbstractSingleFilterOperationProcessPlugin
{
    Q_OBJECT
    Q_INTERFACES(medAbstractSingleFilterOperationProcessPlugin)
    Q_PLUGIN_METADATA(IID "fr.inria.animaSymmetryPlanePlugin" FILE "animaSymmetryPlanePlugin.json")

public:
    animaSymmetryPlanePlugin() {}
    virtual ~animaSymmetryPlanePlugin() {}
    
    virtual void initialize();
    virtual void uninitialize();
};
