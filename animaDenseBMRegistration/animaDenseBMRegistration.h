// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#pragma once

#include <itkProcessRegistration.h>
#include "animaDenseBMRegistrationPluginExport.h"
#include <rpiAnimaDenseBMRegistration.h>

class animaDenseBMRegistrationPrivate;


/**
 * @brief Registration process.
 *
 * This plugin uses the registration programming interface (RPI).
 * It also implements a custom toolbox plugging itself onto the generic registration toolbox available in medInria/src/medGui.
 *
 */
class ANIMADENSEBMREGISTRATIONPLUGIN_EXPORT animaDenseBMRegistration : public itkProcessRegistration
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor.
     *
     * @param void
     */
    animaDenseBMRegistration(void);
    
    /**
     * @brief
     *
     * @param void
     */
    virtual ~animaDenseBMRegistration(void);
    
    /**
     * @brief Description of the plugin.
     *
     * @param void
     * @return QString
     */
    virtual QString description(void) const;
    
    /**
     * @brief tries to register the process with the factory.
     *
     * @param void
     * @return bool true if it succeeded, false otherwise.
     */
    static bool registered(void);
    
    virtual QString identifier(void) const;
    
    virtual itk::Transform<double,3,3>::Pointer getTransform();
    virtual QString getTitleAndParameters();

    typedef float PixelType;
    typedef double TransformScalarType;
    typedef itk::Image< PixelType, 3 > RegImageType;
    //normaly should use long switch cases, but here we know we work with float3 data.
    typedef rpi::AnimaDenseBMRegistration<RegImageType,RegImageType,TransformScalarType> RegistrationType;

public:
    /**
     * @brief Runs the process.
     *
     * @param ImageType the fixed image image type.
     * @return int successful or not.
     */
    virtual int update(ImageType);
    
    void emitProgress(int prog);
    
    /**
     * TODO: this method is not generated by the plugin generator and I think it should be
     */
    virtual void onCanceled (void);
    
    void setBlockSize(int blockSize);

    void setBlockSpacing(unsigned int blockSpacing);
    
    void setStDevThreshold(float StDevThreshold);
    
    void setTransform(unsigned int transform);
    
    void setMetric(unsigned int metric);
    
    void setOptimizer(unsigned int optimizer);
    
    void setMaximumIterations(unsigned int MaximumIterations);
    
    void setMinimalTransformError(float MinimalTransformError);   
    
    void setOptimizerMaximumIterations(unsigned int OptimizerMaximumIterations);    
    
    void setSearchRadius(double SearchRadius);
    
    void setSearchAngleRadius(double SearchAngleRadius);
    
    void setSearchScaleRadius(double SearchScaleRadius);
    
    void setFinalRadius(double FinalRadius);
    
    void setStepSize(double StepSize);
    
    void setTranslateUpperBound(double TranslateUpperBound);
    
    void setAngleUpperBound(double AngleUpperBound);
    
    void setScaleUpperBound(double ScaleUpperBound);
    
    void setAgregator(unsigned int agregator);
    
    void setExtrapolationSigma(double extrapolationSigma);
    
    void setElasticSigma(double elasticSigma);

    void setOutlierSigma(double outlierSigma);
    
    void setMEstimateConvergenceThreshold(double mEstimateConvergenceThreshold);
    
    void setNeighborhoodApproximation(double neighborhoodApproximation);
    
    void setNumberOfPyramidLevels(unsigned int NumberOfPyramidLevels);
    
    void setLastPyramidLevel(unsigned int LastPyramidLevel);
    
    void setPercentageKept(double PercentageKept);

    void setNumberOfThreads(int numberOfThreads);
    
protected :
    /**
     * @brief
     *
     * @param file The path to the file is assumed to be existing. However the file may not exist beforehand.
     * @return bool successful or not.
     */
    virtual bool writeTransform(const QString& file);
    
private:
    animaDenseBMRegistrationPrivate *d;
    
};

/**
 * @brief Function to instantiate the process from the factory.
 * @see registered()
 *
 * @param void
 */
dtkAbstractProcess *createAnimaDenseBMRegistration(void);
