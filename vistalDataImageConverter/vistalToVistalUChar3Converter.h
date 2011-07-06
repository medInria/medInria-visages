#ifndef VISTALTOVISTALUCHAR3CONVERTER_H
#define VISTALTOVISTALUCHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT VistalToVistalUChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             VistalToVistalUChar3Converter(void);
    virtual ~VistalToVistalUChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createVistalToVistalUChar3Converter(void);

#endif
