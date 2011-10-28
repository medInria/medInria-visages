#ifndef VISTALDATAIMAGETOITKDATAIMAGEFLOAT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEFLOAT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageFloat3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageFloat3Converter(void);
    virtual ~vistalDataImageToItkDataImageFloat3Converter(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageFloat3Converter(void);

#endif
