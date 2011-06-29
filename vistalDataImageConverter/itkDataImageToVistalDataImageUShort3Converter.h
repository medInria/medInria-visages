#ifndef ITKDATAIMAGETOVISTALDATAIMAGEUSHORT3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEUSHORT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageUShort3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageUShort3Converter(void);
    virtual ~itkDataImageToVistalDataImageUShort3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageUShort3Converter(void);

#endif
