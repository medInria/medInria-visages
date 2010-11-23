// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalDataImageToItkDataImageUChar3Converter.h"
#include "vistalDataImageToItkDataImageChar3Converter.h"
#include "vistalDataImageToItkDataImageShort3Converter.h"
#include "vistalDataImageToItkDataImageUShort3Converter.h"
#include "vistalDataImageToItkDataImageUInt3Converter.h"
#include "vistalDataImageToItkDataImageInt3Converter.h"
#include "vistalDataImageToItkDataImageFloat3Converter.h"
#include "vistalDataImageToItkDataImageDouble3Converter.h"
#include "vistalDataImageConverterPlugin.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageConverterPluginPrivate
// /////////////////////////////////////////////////////////////////

class vistalDataImageConverterPluginPrivate
{
    public:
        // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// vistalDataImageConverterPlugin
// /////////////////////////////////////////////////////////////////

vistalDataImageConverterPlugin::vistalDataImageConverterPlugin(QObject *parent) :
    dtkPlugin(parent), d(new vistalDataImageConverterPluginPrivate)
{

}

vistalDataImageConverterPlugin::~vistalDataImageConverterPlugin(void)
{
    delete d;

    d = NULL;
}

bool
vistalDataImageConverterPlugin::initialize(void)
{
    if (!vistalDataImageToItkDataImageUChar3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageUChar3Converter type";
    else if (!vistalDataImageToItkDataImageChar3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageChar3Converter type";
    else if (!vistalDataImageToItkDataImageShort3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageShort3Converter type";
    else if (!vistalDataImageToItkDataImageUShort3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageUShort3Converter type";
    else if (!vistalDataImageToItkDataImageUInt3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageUInt3Converter type";
    else if (!vistalDataImageToItkDataImageInt3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageInt3Converter type";
    else if (!vistalDataImageToItkDataImageFloat3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageFloat3Converter type";
    else if (!vistalDataImageToItkDataImageDouble3Converter::registered())
        dtkWarning() << "Unable to register vistalDataImageToItkDataImageDouble3Converter type";
    return true;
}

bool
vistalDataImageConverterPlugin::uninitialize(void)
{
    return true;
}

QString
vistalDataImageConverterPlugin::name(void) const
{
    return "vistalDataImageConverterPlugin";
}

QString
vistalDataImageConverterPlugin::description(void) const
{
    return "Convert vistal data image to something";
}

QStringList
vistalDataImageConverterPlugin::tags(void) const
{
    return QStringList() << "vistal" << "data" << "image" << "converter" << "itk";
}

QStringList
vistalDataImageConverterPlugin::types(void) const
{
    return QStringList() << "vistalDataImageToItkDataImageUChar3Converter" << "vistalDataImageToItkDataImageChar3Converter" << "vistalDataImageToItkDataImageUShort3Converter"
            << "vistalDataImageToItkDataImageShort3Converter" << "vistalDataImageToItkDataImageUInt3Converter" << "vistalDataImageToItkDataImageInt3Converter"
            << "vistalDataImageToItkDataImageFloat3Converter" << "vistalDataImageToItkDataImageDouble3Converter";
}

Q_EXPORT_PLUGIN2(vistalDataImageConverterPlugin, vistalDataImageConverterPlugin)
