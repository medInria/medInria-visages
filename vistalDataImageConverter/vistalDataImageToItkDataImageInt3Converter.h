#ifndef VISTALDATAIMAGETOITKDATAIMAGEINT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageInt3Converter(void);
    virtual ~vistalDataImageToItkDataImageInt3Converter(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageInt3Converter(void);

#endif
