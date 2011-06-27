#ifndef VISTALTOVISTALSHORT3CONVERTER_H
#define VISTALTOVISTALSHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VistalToVistalShort3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalShort3Converter(void);
    virtual ~VistalToVistalShort3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    VistalToVistalShort3ConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalToVistalShort3Converter(void);

#endif
