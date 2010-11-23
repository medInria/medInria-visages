#ifndef ITKDATAIMAGETOVISTALDATAIMAGEINT3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class itkDataImageToVistalDataImageInt3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageInt3Converter(void);
    virtual ~itkDataImageToVistalDataImageInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    itkDataImageToVistalDataImageInt3ConverterPrivate *d;
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageInt3Converter(void);

#endif