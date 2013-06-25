// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaSymmetryPlane.h"
#include "animaSymmetryPlanePlugin.h"
#include "animaSymmetryPlaneToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaSymmetryPlanePluginPrivate
// /////////////////////////////////////////////////////////////////

class animaSymmetryPlanePluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaSymmetryPlanePluginPrivate::s_Name = "animaSymmetryPlane";

// /////////////////////////////////////////////////////////////////
// animaSymmetryPlanePlugin
// /////////////////////////////////////////////////////////////////

animaSymmetryPlanePlugin::animaSymmetryPlanePlugin(QObject *parent) : dtkPlugin(parent), d(new animaSymmetryPlanePluginPrivate)
{

}

animaSymmetryPlanePlugin::~animaSymmetryPlanePlugin(void)
{
    delete d;

    d = NULL;
}

bool animaSymmetryPlanePlugin::initialize(void)
{
    if(!animaSymmetryPlane::registered())
    {
        dtkWarn() << "Unable to register animaSymmetryPlane type";
    }

    if ( !animaSymmetryPlaneToolBox::registered() )
    {
        dtkWarn() << "Unable to register animaSymmetryPlane toolbox";
    }

    return true;
}

bool animaSymmetryPlanePlugin::uninitialize(void)
{
    return true;
}

QString animaSymmetryPlanePlugin::name(void) const
{
    return "animaSymmetryPlanePlugin";
}

QString animaSymmetryPlanePlugin::description(void) const
{
    return "This plugin provides an ITK implementation of inter-hemispheric symmetry plane estimation as proposed by Prima et al.: <a href=\"http://dx.doi.org/10.1117/12.2007075\">http://dx.doi.org/10.1117/12.2007075</a>.";
}

QString animaSymmetryPlanePlugin::version(void) const
{
    return ANIMASYMMETRYPLANEPLUGIN_VERSION;
}

QString animaSymmetryPlanePlugin::contact(void) const
{
    return "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QStringList animaSymmetryPlanePlugin::authors(void) const
{
    return QStringList() << "Guillaume Pasquier <Guillaume.Pasquier@inria.fr>";
}

QStringList animaSymmetryPlanePlugin::contributors(void) const
{
    return QStringList() << "Sylvain Prima <Sylvain.Prima@inria.fr>" << "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QString animaSymmetryPlanePlugin::identifier(void) const
{
    return animaSymmetryPlanePluginPrivate::s_Name;
}

QStringList animaSymmetryPlanePlugin::tags(void) const
{
    return QStringList();
}

QStringList animaSymmetryPlanePlugin::types(void) const
{
    return QStringList() << "animaSymmetryPlane";
}
QStringList animaSymmetryPlanePlugin::dependencies(void) const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(animaSymmetryPlanePlugin, animaSymmetryPlanePlugin)
