#ifndef VISTALDATAIMAGETOITKDATAIMAGEUINT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEUINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageUInt3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageUInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageUInt3Converter(void);
    virtual ~vistalDataImageToItkDataImageUInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageUInt3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageUInt3Converter(void);

#endif