#ifndef ITKDATAIMAGETOVISTALDATAIMAGEUCHAR3CONVERTER_H
#define ITKDATAIMAGETOVISTALDATAIMAGEUCHAR3CONVERTER_H

#include <dtkCore/dtkAbstractDataConverter.h>

#include "vistalDataImageConverterPluginExport.h"

class itkDataImageToVistalDataImageUChar3ConverterPrivate;

class VISTALDATAIMAGECONVERTERPLUGIN_EXPORT itkDataImageToVistalDataImageUChar3Converter : public dtkAbstractDataConverter
{
    Q_OBJECT

public:
             itkDataImageToVistalDataImageUChar3Converter(void);
    virtual ~itkDataImageToVistalDataImageUChar3Converter(void);

    virtual QString description(void) const;
    virtual QStringList fromTypes(void) const;
    virtual QString toType(void) const;

    static bool registered(void);

public slots:
    dtkAbstractData *convert(void);

private:
    itkDataImageToVistalDataImageUChar3ConverterPrivate *d;
};

dtkAbstractDataConverter *createItkDataImageToVistalDataImageUChar3Converter(void);

#endif
