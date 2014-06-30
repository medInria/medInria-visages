// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef VISTALDATAIMAGECHAR3_H
#define VISTALDATAIMAGECHAR3_H

#include <medAbstractImageData.h>

#include <vistalDataImagePluginExport.h>

class vistalDataImageChar3Private;

class VISTALDATAIMAGEPLUGIN_EXPORT vistalDataImageChar3 : public medAbstractImageData
{
    Q_OBJECT
    MED_DATA_INTERFACE("Vistal Image (Char3)",
                       "Vistal Image (Char3)")

public:
             vistalDataImageChar3(void);
    virtual ~vistalDataImageChar3(void);

    static bool registered(void);
	
		virtual QImage &thumbnail(void)   const;
		virtual QList<QImage> &thumbnails (void) const;
	
public slots:
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

#endif
