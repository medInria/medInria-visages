// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGEUSHORT3_H
#define VISTALDATAIMAGEUSHORT3_H

#include <dtkCore/dtkAbstractData.h>
#include <medCore/medAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageUShort3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageUShort3 : public medAbstractDataImage
{
    Q_OBJECT

public:
             vistalDataImageUShort3(void);
    virtual ~vistalDataImageUShort3(void);

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
    vistalDataImageUShort3Private *d;
};

dtkAbstractData *createVistalDataImageUShort3(void);

#endif
