// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "vistalDataImageReader.h"
#include "vistalDataImageReaderPlugin.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageReaderPluginPrivate
// /////////////////////////////////////////////////////////////////

class vistalDataImageReaderPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// vistalDataImageReaderPlugin
// /////////////////////////////////////////////////////////////////

vistalDataImageReaderPlugin::vistalDataImageReaderPlugin(QObject *parent) : dtkPlugin(parent), d(new vistalDataImageReaderPluginPrivate)
{

}

vistalDataImageReaderPlugin::~vistalDataImageReaderPlugin(void)
{
    delete d;

    d = NULL;
}

bool vistalDataImageReaderPlugin::initialize(void)
{
  qDebug() << "Here!!";
    if(!vistalDataImageReader::registered())
	dtkWarning() << "Unable to register vistalDataImageReader type";

    return true;
}

bool vistalDataImageReaderPlugin::uninitialize(void)
{
    return true;
}

QString vistalDataImageReaderPlugin::name(void) const
{
    return "vistalDataImageReaderPlugin";
}

QString vistalDataImageReaderPlugin::description(void) const
{
    return "vistal reader";
}

QStringList vistalDataImageReaderPlugin::tags(void) const
{
    return QStringList() << "vistal" << "data" << "image" << "reader";
}

QStringList vistalDataImageReaderPlugin::types(void) const
{
    return QStringList() << "vistalDataImageReader";
}

Q_EXPORT_PLUGIN2(vistalDataImageReaderPlugin, vistalDataImageReaderPlugin)
