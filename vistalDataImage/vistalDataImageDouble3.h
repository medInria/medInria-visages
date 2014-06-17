// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGEDOUBLE3_H
#define VISTALDATAIMAGEDOUBLE3_H

#include <dtkCore/dtkAbstractData.h>
#include <medAbstractImageData.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageDouble3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageDouble3 : public medAbstractImageData
{
    Q_OBJECT

public:
             vistalDataImageDouble3(void);
    virtual ~vistalDataImageDouble3(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;

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
    vistalDataImageDouble3Private *d;
};

dtkAbstractData *createVistalDataImageDouble3(void);

#endif
