#include "animaPyramidalBMRegistration.h"
#include "animaPyramidalBMRegistrationPlugin.h"
#include "animaPyramidalBMRegistrationToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistrationPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaPyramidalBMRegistrationPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaPyramidalBMRegistrationPluginPrivate::s_Name = "animaPyramidalBMRegistration";

// /////////////////////////////////////////////////////////////////
// animaPyramidalBMRegistrationPlugin
// /////////////////////////////////////////////////////////////////

animaPyramidalBMRegistrationPlugin::animaPyramidalBMRegistrationPlugin(QObject *parent) : dtkPlugin(parent), d(new animaPyramidalBMRegistrationPluginPrivate)
{
    
}

animaPyramidalBMRegistrationPlugin::~animaPyramidalBMRegistrationPlugin(void)
{
    delete d;
    
    d = NULL;
}

bool animaPyramidalBMRegistrationPlugin::initialize(void)
{
    if(!animaPyramidalBMRegistration::registered())
    {
        dtkWarn() << "Unable to register animaPyramidalBMRegistration type";
    }
    
    if(!animaPyramidalBMRegistrationToolBox::registered())
    {
        dtkWarn() << "Unable to register animaPyramidalBMRegistration toolbox";
    }
    
    return true;
}

bool animaPyramidalBMRegistrationPlugin::uninitialize(void)
{
    return true;
}

QString animaPyramidalBMRegistrationPlugin::name(void) const
{
    return "animaPyramidalBMRegistrationPlugin";
}

QString animaPyramidalBMRegistrationPlugin::description(void) const
{
    return "This plugin provides an ITK implementation of global linear block-matching registration.\n It is based on papers by Commowick et al.: <a href=\"http://dx.doi.org/10.1109/ISBI.2012.6235644\">http://dx.doi.org/10.1109/ISBI.2012.6235644</a>, and Ourselin et al.: <a href=\"http://dx.doi.org/10.1007/978-3-540-75757-3\">http://dx.doi.org/10.1007/978-3-540-75757-3</a>.";
}

QString animaPyramidalBMRegistrationPlugin::version(void) const
{
    return ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_VERSION;
}

QString animaPyramidalBMRegistrationPlugin::contact(void) const
{
    return "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QStringList animaPyramidalBMRegistrationPlugin::authors(void) const
{
    return QStringList() << "Guillaume Pasquier <Guillaume.Pasquier@inria.fr>";
}

QStringList animaPyramidalBMRegistrationPlugin::contributors(void) const
{
    return QStringList() << "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QString animaPyramidalBMRegistrationPlugin::identifier(void) const
{
    return animaPyramidalBMRegistrationPluginPrivate::s_Name;
}


QStringList animaPyramidalBMRegistrationPlugin::tags(void) const
{
    return QStringList();
}

QStringList animaPyramidalBMRegistrationPlugin::types(void) const
{
    return QStringList() << "animaPyramidalBMRegistration";
}
QStringList animaPyramidalBMRegistrationPlugin::dependencies(void) const
{
    return QStringList();
}

//Q_EXPORT_PLUGIN2(animaPyramidalBMRegistrationPlugin, animaPyramidalBMRegistrationPlugin)
