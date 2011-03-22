#ifndef ITKDATAIMAGETOVISTALDATAIMAGEDOUBLE3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEDOUBLE3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class itkDataImageToVistalDataImageDouble3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageDouble3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageDouble3Converter(void);
    virtual ~itkDataImageToVistalDataImageDouble3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    itkDataImageToVistalDataImageDouble3ConverterPrivate *d;
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageDouble3Converter(void);

#endif
