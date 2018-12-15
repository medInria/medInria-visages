#include "animaDenseBMRegistration.h"
#include "animaDenseBMRegistrationPlugin.h"
#include "animaDenseBMRegistrationToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaDenseBMRegistrationPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaDenseBMRegistrationPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaDenseBMRegistrationPluginPrivate::s_Name = "animaDenseBMRegistration";

// /////////////////////////////////////////////////////////////////
// animaDenseBMRegistrationPlugin
// /////////////////////////////////////////////////////////////////

animaDenseBMRegistrationPlugin::animaDenseBMRegistrationPlugin(QObject *parent) : dtkPlugin(parent), d(new animaDenseBMRegistrationPluginPrivate)
{
    
}

animaDenseBMRegistrationPlugin::~animaDenseBMRegistrationPlugin(void)
{
    delete d;
    
    d = NULL;
}

bool animaDenseBMRegistrationPlugin::initialize(void)
{
    if(!animaDenseBMRegistration::registered())
    {
        dtkWarn() << "Unable to register animaDenseBMRegistration type";
    }
    
    if(!animaDenseBMRegistrationToolBox::registered())
    {
        dtkWarn() << "Unable to register animaDenseBMRegistration toolbox";
    }
    
    return true;
}

bool animaDenseBMRegistrationPlugin::uninitialize(void)
{
    return true;
}

QString animaDenseBMRegistrationPlugin::name(void) const
{
    return "animaDenseBMRegistrationPlugin";
}

QString animaDenseBMRegistrationPlugin::description(void) const
{
    return "ITK implementation of non linear block-matching based registration. \n It is based on papers by Commowick et al.: <a href=\"https://doi.org/10.1007/978-3-642-33418-4_21\">https://doi.org/10.1007/978-3-642-33418-4_21</a>, and Garcia et al.: <a href=\"http://hal.inria.fr/inria-00616148/en\">http://hal.inria.fr/inria-00616148/en</a>.";
}

QString animaDenseBMRegistrationPlugin::version(void) const
{
    return ANIMADENSEBMREGISTRATIONPLUGIN_VERSION;
}

QString animaDenseBMRegistrationPlugin::contact(void) const
{
    return "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QStringList animaDenseBMRegistrationPlugin::authors(void) const
{
    return QStringList() << "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QStringList animaDenseBMRegistrationPlugin::contributors(void) const
{
    return QStringList() << "";
}

QString animaDenseBMRegistrationPlugin::identifier(void) const
{
    return animaDenseBMRegistrationPluginPrivate::s_Name;
}


QStringList animaDenseBMRegistrationPlugin::tags(void) const
{
    return QStringList();
}

QStringList animaDenseBMRegistrationPlugin::types(void) const
{
    return QStringList() << "animaDenseBMRegistration";
}
QStringList animaDenseBMRegistrationPlugin::dependencies(void) const
{
    return QStringList();
}

//Q_EXPORT_PLUGIN2(animaDenseBMRegistrationPlugin, animaDenseBMRegistrationPlugin)
