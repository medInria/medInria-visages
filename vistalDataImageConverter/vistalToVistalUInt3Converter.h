#ifndef VISTALDATAIMAGETOITKDATAIMAGEUINT3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEUINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VistalToVistalUInt3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalUInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalUInt3Converter(void);
    virtual ~VistalToVistalUInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    VistalToVistalUInt3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalToVistalUInt3Converter(void);

#endif
