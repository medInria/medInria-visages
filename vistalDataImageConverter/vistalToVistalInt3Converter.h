#ifndef VISTALTOVISTALINT3CONVERTER_H
#define VISTALTOVISTALINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalInt3Converter(void);
    virtual ~VistalToVistalInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalToVistalInt3Converter(void);

#endif
