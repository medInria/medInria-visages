#ifndef VISTALDATAIMAGETOITKDATAIMAGESINT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGESINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageSInt3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageSInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageSInt3Converter(void);
    virtual ~vistalDataImageToItkDataImageSInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageSInt3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageSInt3Converter(void);

#endif
