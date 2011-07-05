#ifndef VISTALDATAIMAGETOITKDATAIMAGEDOUBLE3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEDOUBLE3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageDouble3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageDouble3Converter(void);
    virtual ~vistalDataImageToItkDataImageDouble3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageDouble3Converter(void);

#endif
