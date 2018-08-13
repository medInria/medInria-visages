#pragma once

// This example class implements a non rigid algorithm with a displacement field transform, change for rigid or affine.

#include "rpiRegistrationMethod.hxx"

#include "animaPyramidalBlockMatchingBridge.h"


// Namespace RPI : Registration Programming Interface
namespace rpi
{


/**
 * AnimaPyramidalBMRegistration registration method. This is just an interface class to your own registration method. It is here to have
 * a common way of accessing your registration from the registration workspace.
 *
 * There are three templates for this class:
 *
 *   TFixedImage           Type of the fixed image. Must be an itk::Image< TPixel, 3 > where
 *                         TPixel is a scalar type among "float" and "double".
 *
 *   TMovingImage          Type of the moving image. Must be an itk::Image< TPixel, 3 > where
 *                         TPixel is a scalar type among "float" and "double".
 *
 *   TTransformScalarType  Type of the transformation parameters. Must be "float" or "double".
 *
 * In the current implementation, TFixedImage and TMovingImage must be identical.
 *
 */
template < class TFixedImage, class TMovingImage, class TTransformScalarType=double >
class ITK_EXPORT AnimaPyramidalBMRegistration : public RegistrationMethod< TFixedImage, TMovingImage, TTransformScalarType >
{

public:

    typedef typename anima::PyramidalBlockMatchingBridge<TFixedImage::ImageDimension>::AffineTransformType
    TransformType;

    typedef typename anima::PyramidalBlockMatchingBridge<TFixedImage::ImageDimension>::InitializationType
    InitializationType;

    typedef typename TransformType::Pointer
    TransformPointerType;

    typedef anima::PyramidalBlockMatchingBridge <TFixedImage::ImageDimension> PyramidBMType;

protected:

    /**
     * Here go the parameters of the method (number of iterations , ...)
     */

public:

    /**
     * Class constructor.
     */
    AnimaPyramidalBMRegistration ( void );


    /**
     * Class destructor.
     */
    virtual ~AnimaPyramidalBMRegistration ( void );


    /**
     * Setters and getters go here
     */
    void SetInitialTransform( std::string initTransformFile);

    void SetBlockSize ( int blockSize );

    void SetBlockSpacing ( unsigned int blockSpacing );

    void SetStDevThreshold ( float StDevThreshold );

    void SetTransform ( unsigned int transform );

    void SetMetric ( unsigned int metric );

    void SetOptimizer ( unsigned int optimizer );

    void SetMaximumIterations ( unsigned int MaximumIterations );

    void SetMinimalTransformError ( float MinimalTransformError );

    void SetOptimizerMaximumIterations ( unsigned int OptimizerMaximumIterations );

    void SetSearchRadius ( double SearchRadius );

    void SetSearchAngleRadius ( double SearchAngleRadius );

    void SetSearchScaleRadius ( double SearchScaleRadius );

    void SetFinalRadius ( double FinalRadius );

    void SetStepSize ( double StepSize );

    void SetTranslateUpperBound ( double TranslateUpperBound );

    void SetAngleUpperBound ( double AngleUpperBound );

    void SetScaleUpperBound ( double ScaleUpperBound );

    void SetAgregator ( unsigned int agregator );

    void SetOutputTransformType ( unsigned int outputTransform );

    void SetAgregThreshold ( float AgregThreshold );

    void SetSeStoppingThreshold ( float SeStoppingThreshold );

    void SetNumberOfPyramidLevels ( unsigned int NumberOfPyramidLevels );

    void SetLastPyramidLevel ( unsigned int LastPyramidLevel );

    void SetPercentageKept ( double PercentageKept );

    void SetTransformInitializationType (InitializationType InitializeOnCenterOfGravity);

    void SetNumberOfThreads ( int numberOfThreads );

    unsigned int GetNumberOfPyramidLevels ();

    unsigned int GetMaximumIterations ();

    /**
     * Performs the image registration. Must be called before GetTransformation().
     */
    virtual void StartRegistration ( void );

    void Abort ( void );

    void SetProgressCallback(itk::CStyleCommand::Pointer callback );


private:
    typename PyramidBMType::Pointer matcher;
};

} // End of namespace

/** Add the source code file (template) */
#include "rpiAnimaPyramidalBMRegistration.hxx"
