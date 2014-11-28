//// /////////////////////////////////////////////////////////////////
//// Generated by medPluginGenerator
//// /////////////////////////////////////////////////////////////////

#ifndef ANIMALESIONSSEGMENTATIONPLUGIN_H
#define ANIMALESIONSSEGMENTATIONPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "animaLesionsSegmentationPluginExport.h"

class ANIMALESIONSSEGMENTATIONPLUGIN_EXPORT animaLesionsSegmentationPluginPrivate;

class ANIMALESIONSSEGMENTATIONPLUGIN_EXPORT animaLesionsSegmentationPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
    animaLesionsSegmentationPlugin(QObject *parent = 0);
    ~animaLesionsSegmentationPlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString identifier(void) const;
    virtual QString description(void) const;
    virtual QString contact(void) const;
    virtual QString version (void) const;
    virtual QStringList authors(void) const;
    virtual QStringList contributors(void) const;
    virtual QStringList dependencies(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
    animaLesionsSegmentationPluginPrivate *d;
};

#endif
