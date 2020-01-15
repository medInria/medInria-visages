// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#pragma once

#include <medAbstractSelectableToolBox.h>
#include "animaPyramidalBMRegistrationPluginExport.h"

class animaPyramidalBMRegistrationToolBoxPrivate;

class ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_EXPORT animaPyramidalBMRegistrationToolBox : public medAbstractSelectableToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("Linear BM Registration",
                          "Global linear block-matching registration",
                           << "registration")

public:
    animaPyramidalBMRegistrationToolBox(QWidget *parent = 0);
	~animaPyramidalBMRegistrationToolBox();

	dtkPlugin * plugin() override;
	medAbstractData * processOutput() override;

    static bool registered();
    
public slots:
    void run();
    void updateBMOptimizerParams(int);
    void updateBMTransformParams(int);
    void updateBMAgregatorParams(int);
    
private:
    animaPyramidalBMRegistrationToolBoxPrivate *d;
};
