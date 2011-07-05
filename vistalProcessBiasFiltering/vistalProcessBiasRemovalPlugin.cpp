// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalProcessBiasRemoval.h"
#include "vistalProcessBiasRemovalPlugin.h"
#include "vistalProcessBiasRemovalToolBox.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// vistalProcessBiasRemovalPluginPrivate
// /////////////////////////////////////////////////////////////////

class vistalProcessBiasRemovalPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// vistalProcessBiasRemovalPlugin
// /////////////////////////////////////////////////////////////////

vistalProcessBiasRemovalPlugin::vistalProcessBiasRemovalPlugin(QObject *parent) : dtkPlugin(parent), d(new vistalProcessBiasRemovalPluginPrivate)
{

}

vistalProcessBiasRemovalPlugin::~vistalProcessBiasRemovalPlugin(void)
{
    delete d;

    d = NULL;
}

bool vistalProcessBiasRemovalPlugin::initialize(void)
{
    if(!vistalProcessBiasRemoval::registered())
	dtkWarning() << "Unable to register vistalProcessBiasRemoval type";
    
    if(!vistalProcessBiasRemovalToolBox::registered())
	dtkWarning() << "Unable to register vistalProcessBiasRemoval toolbox";

    return true;
}

bool vistalProcessBiasRemovalPlugin::uninitialize(void)
{
    return true;
}

QString vistalProcessBiasRemovalPlugin::name(void) const
{
    return "vistalProcessBiasRemovalPlugin";
}

QString vistalProcessBiasRemovalPlugin::description(void) const
{
    return "Bias (intensity non uniformity) Removal Plugin";
}

QStringList vistalProcessBiasRemovalPlugin::tags(void) const
{
    return QStringList() << "vistal" << "process" << "bias" << "inu" << "preprocessing" << "intensity non uniformity";
}

QStringList vistalProcessBiasRemovalPlugin::types(void) const
{
    return QStringList() << "vistalProcessBiasRemoval";
}

Q_EXPORT_PLUGIN2(vistalProcessBiasRemovalPlugin, vistalProcessBiasRemovalPlugin)
