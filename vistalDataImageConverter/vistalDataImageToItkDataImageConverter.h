#ifndef VISTALDATAIMAGETOITKDATAIMAGECONVERTER_H
#define VISTALDATAIMAGETOITKDATAIMAGECONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class vistalDataImageToItkDataImageConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT vistalDataImageToItkDataImageConverter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             vistalDataImageToItkDataImageConverter(void);
    virtual ~vistalDataImageToItkDataImageConverter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    vistalDataImageToItkDataImageConverterPrivate *d;
};

dtkAbstractDataConverter *createVistalDataImageToItkDataImageConverter(void);

#endif
