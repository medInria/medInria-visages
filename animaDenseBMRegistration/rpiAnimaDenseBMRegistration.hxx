#pragma once
#include "rpiAnimaDenseBMRegistration.h"

// Namespace RPI : Registration Programming Interface
namespace rpi
{
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    AnimaDenseBMRegistration < TFixedImage, TMovingImage, TTransformScalarType >
    ::AnimaDenseBMRegistration ( void )
    {
        // Initialize parameters
        
        // Initialize the transformation
        this->m_transform = TransformType::New();
        
        matcher = BMRegistrationType::New();
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::~AnimaDenseBMRegistration ( void )
    {
        // Do nothing
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::StartRegistration ( void )
    {
        
        // Check if fixed image has been set
        if ( this->m_fixedImage.IsNull() )
            throw std::runtime_error ( "Fixed image has not been set." );
        
        
        // Check if moving image has been set
        if ( this->m_movingImage.IsNull() )
            throw std::runtime_error ( "Moving image has not been set." );
        
        // Local images
        typename  TFixedImage::ConstPointer   fixedImage  = this->m_fixedImage;
        typename  TMovingImage::ConstPointer  movingImage = this->m_movingImage;
        
        typedef itk::Image <double, 3> InternalImageType;
        typedef itk::CastImageFilter <TFixedImage, InternalImageType> CastFilterType;

        typename CastFilterType::Pointer castRefFilter = CastFilterType::New();
        castRefFilter->SetInput(this->m_fixedImage);
        castRefFilter->Update();
        typename CastFilterType::Pointer castFloFilter = CastFilterType::New();
        castFloFilter->SetInput(this->m_movingImage);
        castFloFilter->Update();

        // Set the displacement field to the transformation object
        
        matcher->SetReferenceImage (castRefFilter->GetOutput());
        matcher->SetFloatingImage (castFloFilter->GetOutput());

        matcher->Update();
        
        this->m_transform = matcher->GetOutputDisplacementFieldTransform();
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >::
    SetProgressCallback(itk::CStyleCommand::Pointer callback )
    {
        matcher->SetProgressCallback(callback);
    }
    
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::Abort ( void )
    {
        matcher->Abort();
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetBlockSize ( int blockSize )
    {
        matcher->SetBlockSize ( blockSize );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void
    AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetBlockSpacing ( unsigned int blockSpacing )
    {
        matcher->SetBlockSpacing ( blockSpacing );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetStDevThreshold ( float StDevThreshold )
    {
        matcher->SetStDevThreshold ( StDevThreshold );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetTransform ( unsigned int transform )
    {
        matcher->SetTransform ( ( typename BMRegistrationType::Transform ) transform );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetMetric ( unsigned int metric )
    {
        matcher->SetMetric ( ( typename BMRegistrationType::Metric ) metric );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetOptimizer ( unsigned int optimizer )
    {
        matcher->SetOptimizer ( ( typename BMRegistrationType::Optimizer ) optimizer );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetMaximumIterations ( unsigned int MaximumIterations )
    {
        matcher->SetMaximumIterations ( MaximumIterations );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    unsigned int AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::GetMaximumIterations ()
    {
        return matcher->GetMaximumIterations ();
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetMinimalTransformError ( float MinimalTransformError )
    {
        matcher->SetMinimalTransformError ( MinimalTransformError );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetOptimizerMaximumIterations ( unsigned int OptimizerMaximumIterations )
    {
        matcher->SetOptimizerMaximumIterations ( OptimizerMaximumIterations );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetSearchRadius ( double SearchRadius )
    {
        matcher->SetSearchRadius ( SearchRadius );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetSearchAngleRadius ( double SearchAngleRadius )
    {
        matcher->SetSearchAngleRadius ( SearchAngleRadius );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetSearchScaleRadius ( double SearchScaleRadius )
    {
        matcher->SetSearchScaleRadius ( SearchScaleRadius );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetFinalRadius ( double FinalRadius )
    {
        matcher->SetFinalRadius ( FinalRadius );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetStepSize ( double StepSize )
    {
        matcher->SetStepSize ( StepSize );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetTranslateUpperBound ( double TranslateUpperBound )
    {
        matcher->SetTranslateUpperBound ( TranslateUpperBound );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetAngleUpperBound ( double AngleUpperBound )
    {
        matcher->SetAngleUpperBound ( AngleUpperBound );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetScaleUpperBound ( double ScaleUpperBound )
    {
        matcher->SetScaleUpperBound ( ScaleUpperBound );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetAgregator ( unsigned int agregator )
    {
        matcher->SetAgregator ( ( typename BMRegistrationType::Agregator ) agregator );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetExtrapolationSigma(double extrapolationSigma)
    {
        matcher->SetExtrapolationSigma(extrapolationSigma);
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetElasticSigma(double elasticSigma)
    {
        matcher->SetElasticSigma(elasticSigma);
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetOutlierSigma(double outlierSigma)
    {
        matcher->SetOutlierSigma(outlierSigma);
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetMEstimateConvergenceThreshold(double mEstimateConvergenceThreshold)
    {
        matcher->SetMEstimateConvergenceThreshold(mEstimateConvergenceThreshold);
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetNeighborhoodApproximation(double neighborhoodApproximation)
    {
        matcher->SetNeighborhoodApproximation(neighborhoodApproximation);
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetNumberOfPyramidLevels ( unsigned int NumberOfPyramidLevels )
    {
        matcher->SetNumberOfPyramidLevels ( NumberOfPyramidLevels );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    unsigned int AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::GetNumberOfPyramidLevels ()
    {
        return matcher->GetNumberOfPyramidLevels ();
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetLastPyramidLevel ( unsigned int LastPyramidLevel )
    {
        matcher->SetLastPyramidLevel ( LastPyramidLevel );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetPercentageKept ( double PercentageKept )
    {
        matcher->SetPercentageKept ( PercentageKept );
    }
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    void AnimaDenseBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::SetNumberOfThreads ( int numberOfThreads )
    {
        matcher->SetNumberOfWorkUnits ( numberOfThreads );
    }
    
} // End of namespace
