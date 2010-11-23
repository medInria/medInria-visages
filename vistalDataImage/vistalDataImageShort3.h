// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGESHORT3_H
#define VISTALDATAIMAGESHORT3_H

#include <dtkCore/dtkAbstractDataImage.h>

#include "vistalDataImagePluginExport.h"

class vistalDataImageShort3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageShort3 : public dtkAbstractDataImage
{
    Q_OBJECT

public:
    vistalDataImageShort3(void);
    virtual ~vistalDataImageShort3(void);

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
    vistalDataImageShort3Private *d;
};

dtkAbstractData *createVistalDataImageShort3(void);

#endif
