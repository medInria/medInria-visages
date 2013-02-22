// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaNonLocalMeansFilter.h"
#include "animaNonLocalMeansFilterPlugin.h"
#include "animaNonLocalMeansFilterToolBox.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaNonLocalMeansFilterPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaNonLocalMeansFilterPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaNonLocalMeansFilterPluginPrivate::s_Name = "animaNonLocalMeansFilter";

// /////////////////////////////////////////////////////////////////
// animaNonLocalMeansFilterPlugin
// /////////////////////////////////////////////////////////////////

animaNonLocalMeansFilterPlugin::animaNonLocalMeansFilterPlugin(QObject *parent) : dtkPlugin(parent), d(new animaNonLocalMeansFilterPluginPrivate)
{

}

animaNonLocalMeansFilterPlugin::~animaNonLocalMeansFilterPlugin(void)
{
    delete d;

    d = NULL;
}

bool animaNonLocalMeansFilterPlugin::initialize(void)
{
    if(!animaNonLocalMeansFilter::registered())
        dtkWarn() << "Unable to register animaNonLocalMeansFilter type";

    if ( !animaNonLocalMeansFilterToolBox::registered() )
        dtkWarn() << "Unable to register animaNonLocalMeansFilter toolbox";

    return true;
}

bool animaNonLocalMeansFilterPlugin::uninitialize(void)
{
    return true;
}

QString animaNonLocalMeansFilterPlugin::name(void) const
{
    return "animaNonLocalMeansFilterPlugin";
}

QString animaNonLocalMeansFilterPlugin::description(void) const
{
     return "This plugin provides the NL-Means denoising filter as proposed by Coupe et al.: <a href=\"http://dx.doi.org/10.1109/TMI.2007.906087\">http://dx.doi.org/10.1109/TMI.2007.906087</a>. It also implements 4D NL-Means Rician filtering as proposed by Wiest-Daessle et al.: <a href=\"http://dx.doi.org/10.1109/TMI.2007.906087\">http://dx.doi.org/10.1109/TMI.2007.906087</a>. \n 3D and 4D images are supported.";
}

QString animaNonLocalMeansFilterPlugin::version(void) const
{
    return ANIMANONLOCALMEANSFILTERPLUGIN_VERSION;
}

QString animaNonLocalMeansFilterPlugin::contact(void) const
{
    return "Olivier Commowick <Olivier.Commowick@inria.fr>";
}

QStringList animaNonLocalMeansFilterPlugin::authors(void) const
{
    return QStringList() << "Rene-Paul Debroize <Rene-Paul.Debroize@inria.fr>";
}

QStringList animaNonLocalMeansFilterPlugin::contributors(void) const
{
    return QStringList() << "Rene-Paul Debroize <Rene-Paul.Debroize@inria.fr>";
}

QString animaNonLocalMeansFilterPlugin::identifier(void) const
{
    return animaNonLocalMeansFilterPluginPrivate::s_Name;
}


QStringList animaNonLocalMeansFilterPlugin::tags(void) const
{
    return QStringList();
}

QStringList animaNonLocalMeansFilterPlugin::types(void) const
{
    return QStringList() << "animaNonLocalMeansFilter";
}
QStringList animaNonLocalMeansFilterPlugin::dependencies(void) const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(animaNonLocalMeansFilterPlugin, animaNonLocalMeansFilterPlugin)
