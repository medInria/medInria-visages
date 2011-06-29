#ifndef VISTALDATAIMAGETOITKDATAIMAGESHORT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGESHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageShort3Converter(void);
    virtual ~vistalDataImageToItkDataImageShort3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageShort3Converter(void);

#endif
