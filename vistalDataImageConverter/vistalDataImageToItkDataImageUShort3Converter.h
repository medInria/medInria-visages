#ifndef VISTALDATAIMAGETOITKDATAIMAGEUSHORT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEUSHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageUShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageUShort3Converter(void);
    virtual ~vistalDataImageToItkDataImageUShort3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageUShort3Converter(void);

#endif
