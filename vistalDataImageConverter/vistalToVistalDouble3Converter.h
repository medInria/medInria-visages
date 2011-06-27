#ifndef VISTALDATAIMAGETOITKDATAIMAGEDOUBLE3CONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGEDOUBLE3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VistalToVistalDouble3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalDouble3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalDouble3Converter(void);
    virtual ~VistalToVistalDouble3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    VistalToVistalDouble3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalToVistalDouble3Converter(void);

#endif
