// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGESINT3_H
#define VISTALDATAIMAGESINT3_H

#include <dtkCore/dtkAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageSInt3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageSInt3 : public dtkAbstractDataImage
{
    Q_OBJECT

public:
             vistalDataImageSInt3(void);
    virtual ~vistalDataImageSInt3(void);

    virtual QString description(void) const;

    static bool registered(void);
	
		virtual QImage &thumbnail(void)   const;
		virtual QList<QImage> &thumbnails (void) const;
	
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
    vistalDataImageSInt3Private *d;
};

dtkAbstractData *createVistalDataImageSInt3(void);

#endif
