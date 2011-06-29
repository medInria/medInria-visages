#ifndef ITKDATAIMAGETOVISTALDATAIMAGEUINT3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEUINT3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"


class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageUInt3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageUInt3Converter(void);
    virtual ~itkDataImageToVistalDataImageUInt3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageUInt3Converter(void);

#endif
