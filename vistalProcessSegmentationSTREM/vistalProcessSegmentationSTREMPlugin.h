// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALPROCESSSEGMENTATIONPLUGIN_H
#define VISTALPROCESSSEGMENTATIONPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "vistalProcessSegmentationPluginExport.h"

class VISTALPROCESSSEGMENTATIONPLUGIN_EXPORT vistalProcessSegmentationPluginPrivate;

class VISTALPROCESSSEGMENTATIONPLUGIN_EXPORT vistalProcessSegmentationPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     vistalProcessSegmentationPlugin(QObject *parent = 0);
    ~vistalProcessSegmentationPlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
     vistalProcessSegmentationPluginPrivate *d;
};

#endif
