// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "animaLesionsSegmentation.h"
#include "animaLesionsSegmentationPlugin.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaLesionsSegmentationPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaLesionsSegmentationPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaLesionsSegmentationPluginPrivate::s_Name = "animaLesionsSegmentation";

// /////////////////////////////////////////////////////////////////
// animaLesionsSegmentationPlugin
// /////////////////////////////////////////////////////////////////

animaLesionsSegmentationPlugin::animaLesionsSegmentationPlugin(QObject *parent) : dtkPlugin(parent), d(new animaLesionsSegmentationPluginPrivate)
{

}

animaLesionsSegmentationPlugin::~animaLesionsSegmentationPlugin(void)
{
    delete d;
    d = NULL;
}

bool animaLesionsSegmentationPlugin::initialize(void)
{
    if(!animaLesionsSegmentation::registered())
    {
        dtkWarn() << "Unable to register animaLesionsSegmentation type";
    }

    return true;
}

bool animaLesionsSegmentationPlugin::uninitialize(void)
{
    return true;
}

QString animaLesionsSegmentationPlugin::name(void) const
{
    return "animaLesionsSegmentationPlugin";
}

QString animaLesionsSegmentationPlugin::description(void) const
{
     return "This plugin for segmentation...";
}

QString animaLesionsSegmentationPlugin::version(void) const
{
    return ANIMALESIONSSEGMENTATIONPLUGIN_VERSION;
}

QString animaLesionsSegmentationPlugin::contact(void) const
{
    return "...";
}

QStringList animaLesionsSegmentationPlugin::authors(void) const
{
    return QStringList() << "...";
}

QStringList animaLesionsSegmentationPlugin::contributors(void) const
{
    return QStringList() << "...";
}

QString animaLesionsSegmentationPlugin::identifier(void) const
{
    return animaLesionsSegmentationPluginPrivate::s_Name;
}


QStringList animaLesionsSegmentationPlugin::tags(void) const
{
    return QStringList();
}

QStringList animaLesionsSegmentationPlugin::types(void) const
{
    return QStringList() << "animaLesionsSegmentation";
}
QStringList animaLesionsSegmentationPlugin::dependencies(void) const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(animaLesionsSegmentationPlugin, animaLesionsSegmentationPlugin)