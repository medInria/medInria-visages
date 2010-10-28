// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGESSHORT3_H
#define VISTALDATAIMAGESSHORT3_H

#include <dtkCore/dtkAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageSShort3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageSShort3 : public dtkAbstractData
{
    Q_OBJECT

public:
             vistalDataImageSShort3(void);
    virtual ~vistalDataImageSShort3(void);

    virtual QString description(void) const;

    static bool registered(void);

public slots:
    // derived from dtkAbstractData
    
    void *output(void);
    void *data(void);
    void setData(void* data);

 public:
    int xDimension(void);
    int yDimension(void);
    int zDimension(void);
    int tDimension(void);

private:
    vistalDataImageSShort3Private *d;
};

dtkAbstractData *createVistalDataImageSShort3(void);

#endif
