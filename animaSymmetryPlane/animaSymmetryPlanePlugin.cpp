#include <animaSymmetryPlanePlugin.h>

#include <medCore.h>
#include <medWidgets.h>

#include <animaSymmetryPlaneProcess.h>
#include <animaSymmetryPlaneProcessPresenter.h>

void animaSymmetryPlanePlugin::initialize()
{
    medCore::singleFilterOperation::symmetryAlignment::pluginFactory().record(animaSymmetryPlaneProcess::staticMetaObject.className(),
                                                                              animaSymmetryPlaneProcessCreator);

    medWidgets::singleFilterOperation::symmetryAlignment::presenterFactory().record(animaSymmetryPlaneProcess::staticMetaObject.className(),
                                                                                    animaSymmetryPlaneProcessPresenterCreator);
}

void animaSymmetryPlanePlugin::uninitialize()
{
}

DTK_DEFINE_PLUGIN(animaSymmetryPlaneProcess)
DTK_DEFINE_PLUGIN(animaSymmetryPlaneProcessPresenter)
