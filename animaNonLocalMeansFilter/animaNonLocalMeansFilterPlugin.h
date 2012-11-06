// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ANIMANONLOCALMEANSFILTERPLUGIN_H
#define ANIMANONLOCALMEANSFILTERPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "animaNonLocalMeansFilterPluginExport.h"

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterPluginPrivate;

class ANIMANONLOCALMEANSFILTERPLUGIN_EXPORT animaNonLocalMeansFilterPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
    animaNonLocalMeansFilterPlugin(QObject *parent = 0);
    ~animaNonLocalMeansFilterPlugin(void);

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
    animaNonLocalMeansFilterPluginPrivate *d;
};

#endif
