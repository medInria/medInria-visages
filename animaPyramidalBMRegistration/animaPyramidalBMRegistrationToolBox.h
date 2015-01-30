// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#pragma once

#include <medRegistrationAbstractToolBox.h>
#include "animaPyramidalBMRegistrationPluginExport.h"

class animaPyramidalBMRegistrationToolBoxPrivate;

class ANIMAPYRAMIDALBMREGISTRATIONPLUGIN_EXPORT animaPyramidalBMRegistrationToolBox : public medRegistrationAbstractToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("Linear BM Registration",
                          "Global linear block-matching registration",
                           << "registration")

public:
    animaPyramidalBMRegistrationToolBox(QWidget *parent = 0);
    ~animaPyramidalBMRegistrationToolBox(void);
    
    static bool registered(void);

    int blockSize() const;
    unsigned int blockSpacing() const;
    float stDevThreshold() const;
    unsigned int transform() const;
    unsigned int metric() const;
    unsigned int optimizer() const;
    unsigned int maximumIterations() const;
    float minimalTransformError() const;
    unsigned int optimizerMaximumIterations() const;
    double searchRadius() const;
    double searchAngleRadius() const;
    double searchSkewRadius() const;
    double searchScaleRadius() const;
    double finalRadius() const;
    double stepSize() const;
    double translateUpperBound() const;
    double angleUpperBound() const;
    double skewUpperBound() const;
    double scaleUpperBound() const;
    unsigned int agregator() const;
    unsigned int outputTransformType() const;
    float agregThreshold() const;
    float seStoppingThreshold() const;
    unsigned int numberOfPyramidLevels() const;
    unsigned int lastPyramidLevel() const;
    double percentageKept() const;
    bool initializeOnCenterOfGravity() const;
    int numberOfThreads() const;
    
public slots:
    void run(void);
    void updateBMOptimizerParams(int);
    void updateBMTransformParams(int);
    void updateBMAgregatorParams(int);
    
private:
    animaPyramidalBMRegistrationToolBoxPrivate *d;
};
