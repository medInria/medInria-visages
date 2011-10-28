#ifndef VISTALTOVISTALUSHORT3CONVERTER_H
#define VISTALTOVISTALUSHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalUShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalUShort3Converter(void);
    virtual ~VistalToVistalUShort3Converter(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalToVistalUShort3Converter(void);

#endif
