#include <animaTensorEstimationPlugin.h>

#include <medCore.h>
#include <medWidgets.h>
#include <animaTensorEstimationProcess.h>
#include <animaTensorEstimationProcessPresenter.h>

void animaTensorEstimationPlugin::initialize(void)
{
    medCore::diffusionModelEstimation::pluginFactory().record(animaTensorEstimationProcess::staticMetaObject.className(),
                                                              animaTensorEstimationProcessCreator);

    medWidgets::diffusionModelEstimation::presenterFactory().record(animaTensorEstimationProcess::staticMetaObject.className(),
                                                                    animaTensorEstimationProcessPresenterCreator);
}

void animaTensorEstimationPlugin::uninitialize(void)
{
}

DTK_DEFINE_PLUGIN(animaTensorEstimationProcess)
DTK_DEFINE_PLUGIN(animaTensorEstimationProcessPresenter)
