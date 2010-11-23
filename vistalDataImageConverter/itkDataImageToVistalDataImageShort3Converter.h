#ifndef ITKDATAIMAGETOVISTALDATAIMAGESHORT3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGESHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class itkDataImageToVistalDataImageShort3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageShort3Converter(void);
    virtual ~itkDataImageToVistalDataImageShort3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    itkDataImageToVistalDataImageShort3ConverterPrivate *d;
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageShort3Converter(void);

#endif