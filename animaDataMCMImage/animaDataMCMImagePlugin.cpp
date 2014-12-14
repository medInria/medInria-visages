#include <animaDataMCMImagePlugin.h>

#include <animaDataMCMImageDouble3.h>
#include <animaDataMCMImageFloat3.h>
#include <animaDataMCMImageVtkViewInteractor.h>

#include <animaDataMCMImageReader.h>
#include <animaMetaDataMCMImageWriter.h>
#include <animaNiftiDataMCMImageWriter.h>

#include <dtkLog/dtkLog.h>
#include <itkLogForwarder.h>

// /////////////////////////////////////////////////////////////////
// animaDataMCMImagePluginPrivate
// /////////////////////////////////////////////////////////////////

class animaDataMCMImagePluginPrivate
{
public:

    animaDataMCMImagePluginPrivate() { forwarder = itk::LogForwarder::New(); }
    ~animaDataMCMImagePluginPrivate() { }

    // Class variables go here.

    itk::LogForwarder::Pointer forwarder;
};

// /////////////////////////////////////////////////////////////////
// animaDataMCMImagePlugin
// /////////////////////////////////////////////////////////////////

animaDataMCMImagePlugin::animaDataMCMImagePlugin(QObject *parent): dtkPlugin(parent),d(new animaDataMCMImagePluginPrivate)
{

}

animaDataMCMImagePlugin::~animaDataMCMImagePlugin()
{
    delete d;
    d = NULL;
}

bool animaDataMCMImagePlugin::initialize()
{
    if (!animaDataMCMImageDouble3::registered()) { dtkWarn() << "Unable to register animaDataMCMImageDouble3 type"; }
    if (!animaDataMCMImageFloat3::registered()) { dtkWarn() << "Unable to register animaDataMCMImageFloat3 type"; }
    if (!animaDataMCMImageVtkViewInteractor::registered()) { dtkWarn() << "Unable to register animaDataMCMImageVtkViewInteractor type"; }

    if (!animaDataMCMImageReader::registered()) { dtkWarn() << "Unable to register animaDataMCMImageReader type"; }
    if (!animaMetaDataMCMImageWriter::registered()) { dtkWarn() << "Unable to register animaMetaDataMCMImageWriter type"; }
    if (!animaNiftiDataMCMImageWriter::registered()) { dtkWarn() << "Unable to register animaNiftiDataMCMImageWriter type"; }

    return true;
}

bool animaDataMCMImagePlugin::uninitialize()
{
    return true;
}

QString animaDataMCMImagePlugin::name() const
{
    return "animaDataMCMImagePlugin";
}

QString animaDataMCMImagePlugin::contact() const
{
    return QString::fromUtf8("Olivier Commowick <Olivier.Commowick@inria.fr>");
}

QStringList animaDataMCMImagePlugin::authors() const
{
    QStringList list;
    list << QString::fromUtf8("Aymeric Stamm") << QString::fromUtf8("Olivier Commowick");
    return list;
}

QStringList animaDataMCMImagePlugin::contributors() const
{
    return QStringList();
}

QString animaDataMCMImagePlugin::version() const
{
    return ANIMADATAMCMIMAGEPLUGIN_VERSION;
}

QString animaDataMCMImagePlugin::description() const
{
    return "Multi-compartment models dat aand visualization";
}

QStringList animaDataMCMImagePlugin::tags() const
{
    return QStringList() << "anima" << "data" << "MCM" << "image" << "reader" << "writer";
}

QStringList animaDataMCMImagePlugin::types() const
{
    return QStringList() << "animaDataMCMImageFloat3"
                         << "animaDataMCMImageDouble3"
                         << "animaDataMCMImageReader"
                         << "animaDataMCMImageWriter";
}

Q_EXPORT_PLUGIN2(animaDataMCMImagePlugin, animaDataMCMImagePlugin)
