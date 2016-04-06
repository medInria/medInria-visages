#include <animaNonLocalMeansFilterPlugin.h>

#include <medCore.h>
#include <medWidgets.h>

#include <animaNonLocalMeansFilterProcess.h>
#include <animaNonLocalMeansFilterProcessPresenter.h>

void animaNonLocalMeansFilterPlugin::initialize()
{
    medCore::singleFilterOperation::imageDenoising::pluginFactory().record(animaNonLocalMeansFilterProcess::staticMetaObject.className(),
                                                                           animaNonLocalMeansFilterProcessCreator);

    medWidgets::singleFilterOperation::imageDenoising::presenterFactory().record(animaNonLocalMeansFilterProcess::staticMetaObject.className(),
                                                                                 animaNonLocalMeansFilterProcessPresenterCreator);
}

void animaNonLocalMeansFilterPlugin::uninitialize()
{
}

DTK_DEFINE_PLUGIN(animaNonLocalMeansFilterProcess)
DTK_DEFINE_PLUGIN(animaNonLocalMeansFilterProcessPresenter)
