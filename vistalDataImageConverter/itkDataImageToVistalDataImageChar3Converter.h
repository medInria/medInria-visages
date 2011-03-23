#ifndef ITKDATAIMAGETOVISTALDATAIMAGECHAR3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGECHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class itkDataImageToVistalDataImageChar3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageChar3Converter(void);
    virtual ~itkDataImageToVistalDataImageChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    itkDataImageToVistalDataImageChar3ConverterPrivate *d;
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageChar3Converter(void);

#endif
