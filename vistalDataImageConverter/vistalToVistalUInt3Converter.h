#ifndef VISTALTOVISTALUINT3CONVERTER_H
#define VISTALTOVISTALUINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"
class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalUInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalUInt3Converter(void);
    virtual ~VistalToVistalUInt3Converter(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalToVistalUInt3Converter(void);

#endif
