#ifndef ITKDATAIMAGETOVISTALDATAIMAGEFLOAT3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEFLOAT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageFloat3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageFloat3Converter(void);
    virtual ~itkDataImageToVistalDataImageFloat3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageFloat3Converter(void);

#endif
