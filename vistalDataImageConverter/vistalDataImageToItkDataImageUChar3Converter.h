#ifndef VISTALDATAIMAGETOITKDATAIMAGEUCHAR3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEUCHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageUChar3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageUChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageUChar3Converter(void);
    virtual ~vistalDataImageToItkDataImageUChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageUChar3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageUChar3Converter(void);

#endif
