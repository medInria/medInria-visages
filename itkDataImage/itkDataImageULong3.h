#ifndef _itk_DataImageULong3_h_
#define _itk_DataImageULong3_h_

#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkGlobal.h>

#include "itkDataImagePluginExport.h"


class itkDataImageULong3Private;

class ITKDATAIMAGEPLUGIN_EXPORT itkDataImageULong3 : public dtkAbstractDataImage
{
  Q_OBJECT
    
 public:
    itkDataImageULong3(void);
    ~itkDataImageULong3(void);
    virtual QString description(void) const;
    static bool registered(void);

    virtual QImage        &thumbnail(void)   const;
    virtual QList<QImage> &thumbnails (void) const;

 public slots:
    // derived from dtkAbstractData
    
    void *output(void);
    void *data(void);
    void setData(void* data);
    void update(void);

    void onMetaDataSet(const QString& key, const QString& value);
    void onPropertySet(const QString& key, const QString& value);

 public:
    // derived from dtkAbstractDataImage

    int xDimension(void);
    int yDimension(void);
    int zDimension(void);
	int tDimension(void);

    int minRangeValue(void);
    int maxRangeValue(void);

    int scalarValueCount(int value);
    int scalarValueMinCount(void);
    int scalarValueMaxCount(void);
    
 private:
    void computeRange(void);
    void computeValueCounts(void);

    itkDataImageULong3Private* d;
  
};

dtkAbstractData* createItkDataImageULong3 (void);

#endif
