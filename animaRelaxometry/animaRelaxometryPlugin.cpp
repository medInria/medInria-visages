#include <animaRelaxometryPlugin.h>

#include <medCore.h>
#include <medWidgets.h>

#include <animaDESPOT1RelaxometryProcess.h>
#include <animaDESPOT1RelaxometryProcessPresenter.h>
#include <animaT2RelaxometryProcess.h>
#include <animaT2RelaxometryProcessPresenter.h>

void animaRelaxometryPlugin::initialize()
{
    medCore::singleFilterOperation::relaxometryEstimation::pluginFactory().record(animaDESPOT1RelaxometryProcess::staticMetaObject.className(),
                                                                                  animaDESPOT1RelaxometryProcessCreator);

    medWidgets::singleFilterOperation::relaxometryEstimation::presenterFactory().record(animaDESPOT1RelaxometryProcess::staticMetaObject.className(),
                                                                                        animaDESPOT1RelaxometryProcessPresenterCreator);

    medCore::singleFilterOperation::relaxometryEstimation::pluginFactory().record(animaT2RelaxometryProcess::staticMetaObject.className(),
                                                                                  animaT2RelaxometryProcessCreator);

    medWidgets::singleFilterOperation::relaxometryEstimation::presenterFactory().record(animaT2RelaxometryProcess::staticMetaObject.className(),
                                                                                        animaT2RelaxometryProcessPresenterCreator);
}

void animaRelaxometryPlugin::uninitialize()
{
}

DTK_DEFINE_PLUGIN(animaDESPOT1RelaxometryProcess)
DTK_DEFINE_PLUGIN(animaDESPOT1RelaxometryProcessPresenter)
DTK_DEFINE_PLUGIN(animaT2RelaxometryProcess)
DTK_DEFINE_PLUGIN(animaT2RelaxometryProcessPresenter)
