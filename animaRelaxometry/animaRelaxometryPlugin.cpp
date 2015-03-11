/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <animaDESPOT1Relaxometry.h>
#include <animaRelaxometryPlugin.h>
#include <animaDESPOT1RelaxometryToolBox.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// animaRelaxometryPluginPrivate
// /////////////////////////////////////////////////////////////////

class animaRelaxometryPluginPrivate
{
public:
    // Class variables go here.
    static const char *s_Name;
};

const char * animaRelaxometryPluginPrivate::s_Name = "animaRelaxometry";

// /////////////////////////////////////////////////////////////////
// animaRelaxometryPlugin
// /////////////////////////////////////////////////////////////////

animaRelaxometryPlugin::animaRelaxometryPlugin(QObject *parent) : dtkPlugin(parent), d(new animaRelaxometryPluginPrivate)
{
    
}

animaRelaxometryPlugin::~animaRelaxometryPlugin()
{
    delete d;
    
    d = NULL;
}

bool animaRelaxometryPlugin::initialize()
{
    if(!animaDESPOT1Relaxometry::registered())
    {
        dtkWarn() << "Unable to register animaDESPOT1Relaxometry type";
    }

    if ( !animaDESPOT1RelaxometryToolBox::registered() )
    {
        dtkWarn() << "Unable to register animaDESPOT1Relaxometry toolbox";
    }

    return true;
}

bool animaRelaxometryPlugin::uninitialize()
{
    return true;
}

QString animaRelaxometryPlugin::name() const
{
    return "animaRelaxometryPlugin";
}

QString animaRelaxometryPlugin::description() const
{
    return tr("AnimaRelaxometry");
}

QString animaRelaxometryPlugin::version() const
{
    return ANIMARELAXOMETRYPLUGIN_VERSION;
}

QString animaRelaxometryPlugin::contact() const
{
    return "";
}

QStringList animaRelaxometryPlugin::authors() const
{
    QStringList list;
    return list;
}

QStringList animaRelaxometryPlugin::contributors() const
{
    QStringList list;
    return list;
}

QString animaRelaxometryPlugin::identifier() const
{
    return animaRelaxometryPluginPrivate::s_Name;
}


QStringList animaRelaxometryPlugin::tags() const
{
    return QStringList();
}

QStringList animaRelaxometryPlugin::types() const
{
    return QStringList() << "animaRelaxometry";
}
QStringList animaRelaxometryPlugin::dependencies() const
{
    return QStringList();
}
Q_EXPORT_PLUGIN2(animaRelaxometryPlugin, animaRelaxometryPlugin)
