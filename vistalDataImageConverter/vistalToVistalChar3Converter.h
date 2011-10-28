#ifndef VISTALTOVISTALCHAR3CONVERTER_H
#define VISTALTOVISTALCHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalChar3Converter(void);
    virtual ~VistalToVistalChar3Converter(void);

    virtual QString description(void) const;
    virtual QString identifier(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalToVistalChar3Converter(void);

#endif
