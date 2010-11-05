#ifndef VISTALDATAIMAGETOITKDATAIMAGESCHAR3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGESCHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageSChar3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageSChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageSChar3Converter(void);
    virtual ~vistalDataImageToItkDataImageSChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageSChar3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageSChar3Converter(void);

#endif
