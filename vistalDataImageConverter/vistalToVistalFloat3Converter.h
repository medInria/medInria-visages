#ifndef VISTALDATAIMAGETOITKDATAIMAGEFLOAT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEFLOAT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VistalToVistalFloat3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalFloat3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalFloat3Converter(void);
    virtual ~VistalToVistalFloat3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    VistalToVistalFloat3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalToVistalFloat3Converter(void);

#endif
