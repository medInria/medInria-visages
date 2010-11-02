// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalDataImageToItkDataImageConverter.h"
#include "itkImage3D.hh"

#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageToItkDataImageConverterPrivate
// /////////////////////////////////////////////////////////////////

class vistalDataImageToItkDataImageConverterPrivate
{
    public:
        itkImage3D<unsigned char> * uchar3Converter;
        itkImage3D<unsigned short> * ushort3Converter;
        itkImage3D<short> * sshort3Converter;

        dtkAbstractData * output;

};

// /////////////////////////////////////////////////////////////////
// vistalDataImageToItkDataImageConverter
// /////////////////////////////////////////////////////////////////

vistalDataImageToItkDataImageConverter::vistalDataImageToItkDataImageConverter(void) :
    dtkAbstractDataConverter(), d(new vistalDataImageToItkDataImageConverterPrivate)
{
    d->output = dtkAbstractDataFactory::instance()->create("itkDataImageShort3");
    d->uchar3Converter = NULL;
    d->ushort3Converter = NULL;
    d->sshort3Converter = NULL;
}

vistalDataImageToItkDataImageConverter::~vistalDataImageToItkDataImageConverter(void)
{

}

bool
vistalDataImageToItkDataImageConverter::registered(void)
{
    return dtkAbstractDataFactory::instance()->registerDataConverterType("vistalDataImageToItkDataImageConverter", QStringList() << "vistalDataImageUChar3" << "vistalDataImageUShort3"
            << "vistalDataImageSShort3", "itkDataImageShort3", createVistalDataImageToItkDataImageConverter);
}

QString
vistalDataImageToItkDataImageConverter::description(void) const
{
    return "vistalDataImageToItkDataImageConverter";
}

QStringList
vistalDataImageToItkDataImageConverter::fromTypes(void) const
{
    return QStringList() << "vistalDataImageUChar3" << "vistalDataImageUShort3" << "vistalDataImageSShort3";
}

QString
vistalDataImageToItkDataImageConverter::toType(void) const
{
    return "itkDataImageShort3";
}

dtkAbstractData *
vistalDataImageToItkDataImageConverter::convert(void)
{

    return d->output;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataConverter *
createVistalDataImageToItkDataImageConverter(void)
{
    return new vistalDataImageToItkDataImageConverter;
}
