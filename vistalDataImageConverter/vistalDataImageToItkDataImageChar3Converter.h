#ifndef VISTALDATAIMAGETOITKDATAIMAGECHAR3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGECHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageChar3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageChar3Converter(void);
    virtual ~vistalDataImageToItkDataImageChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageChar3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageChar3Converter(void);

#endif
