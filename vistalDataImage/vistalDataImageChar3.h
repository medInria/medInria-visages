// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGECHAR3_H
#define VISTALDATAIMAGECHAR3_H

#include <dtkCore/dtkAbstractData.h>

// #include <dtkCore/dtkAbstractDataImage.h>

// #include <medCore/medAbstractData.h>
#include <medCore/medAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageChar3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageChar3 : public medAbstractDataImage
{
    Q_OBJECT

public:
             vistalDataImageChar3(void);
    virtual ~vistalDataImageChar3(void);

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

	int minRangeValue(void);
	int maxRangeValue(void);
	
private:
    vistalDataImageChar3Private *d;
};

dtkAbstractData *createVistalDataImageChar3(void);

#endif
