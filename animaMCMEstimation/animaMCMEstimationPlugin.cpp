#include <animaMCMEstimationPlugin.h>

#include <medCore.h>
#include <medWidgets.h>
#include <animaMCMEstimationProcess.h>
#include <animaMCMEstimationProcessPresenter.h>

void animaMCMEstimationPlugin::initialize(void)
{
    medCore::diffusionModelEstimation::pluginFactory().record(animaMCMEstimationProcess::staticMetaObject.className(),
                                                              animaMCMEstimationProcessCreator);

    medWidgets::diffusionModelEstimation::presenterFactory().record(animaMCMEstimationProcess::staticMetaObject.className(),
                                                                    animaMCMEstimationProcessPresenterCreator);
}

void animaMCMEstimationPlugin::uninitialize(void)
{
}

DTK_DEFINE_PLUGIN(animaMCMEstimationProcess)
DTK_DEFINE_PLUGIN(animaMCMEstimationProcessPresenter)
