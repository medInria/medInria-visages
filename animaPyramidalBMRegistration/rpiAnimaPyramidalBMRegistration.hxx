#pragma once

// Namespace RPI : Registration Programming Interface
namespace rpi
{

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
AnimaPyramidalBMRegistration < TFixedImage, TMovingImage, TTransformScalarType >
::AnimaPyramidalBMRegistration ( void )
{
    // Initialize parameters

    // Initialize the transformation
    this->m_transform = TransformType::New();

    matcher = PyramidBMType::New();
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::~AnimaPyramidalBMRegistration ( void )
{
    // Do nothing
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::StartRegistration ( void )
{

    // Check if fixed image has been set
    if ( this->m_fixedImage.IsNull() )
        throw std::runtime_error ( "Fixed image has not been set." );


    // Check if moving image has been set
    if ( this->m_movingImage.IsNull() )
        throw std::runtime_error ( "Moving image has not been set." );


    // Type definition
    typedef  typename  TransformType::ScalarType
    ScalarType;

    // Local images
    typename  TFixedImage::ConstPointer   fixedImage  = this->m_fixedImage;
    typename  TMovingImage::ConstPointer  movingImage = this->m_movingImage;

    // Set the displacement field to the transformation object

    matcher->SetReferenceImage ( this->m_fixedImage );
    matcher->SetFloatingImage ( this->m_movingImage );

    
    typedef BaseTransformAgregator < TFixedImage::ImageDimension > AgregatorType;
    typedef itk::AffineTransform<typename AgregatorType::ScalarType,TFixedImage::ImageDimension> AffineTransformType;
    typedef typename AffineTransformType::Pointer AffineTransformPointer;

    AffineTransformPointer tmpTrsf = AffineTransformType::New();
    tmpTrsf->SetIdentity();
    matcher->SetOutputTransform ( tmpTrsf.GetPointer() );

    matcher->Update();

    this->m_transform = matcher->GetOutputTransform();

    // This will be done from your registration output, using something similar to this for non rigid transforms
    /*  static_cast< TransformType * >(this->m_transform.GetPointer())->SetParametersAsVectorField(
          static_cast<typename VectorFieldType::ConstPointer>(matcher->GetOutputImage()));*/
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void 
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >::
SetProgressCallback(itk::CStyleCommand::Pointer callback )
{
    matcher->SetProgressCallback(callback);    
}
    

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void 
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::Abort ( void )
{
    matcher->Abort(); 
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetInitialTransform( std::string initTransformFile)
{
    matcher->SetInitialTransform ( initTransformFile );
}
    
template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetBlockSize ( int blockSize )
{
    matcher->SetBlockSize ( blockSize );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void
AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetBlockSpacing ( unsigned int blockSpacing )
{
    matcher->SetBlockSpacing ( blockSpacing );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetStDevThreshold ( float StDevThreshold )
{
    matcher->SetStDevThreshold ( StDevThreshold );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetTransform ( unsigned int transform )
{
    matcher->SetTransform ( ( Transform ) transform );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetMetric ( unsigned int metric )
{
    matcher->SetMetric ( ( Metric ) metric );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetOptimizer ( unsigned int optimizer )
{
    matcher->SetOptimizer ( ( Optimizer ) optimizer );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetMaximumIterations ( unsigned int MaximumIterations )
{
    matcher->SetMaximumIterations ( MaximumIterations );
}
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    unsigned int AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::GetMaximumIterations ()
    {
        return matcher->GetMaximumIterations ();
    }

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetMinimalTransformError ( float MinimalTransformError )
{
    matcher->SetMinimalTransformError ( MinimalTransformError );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetOptimizerMaximumIterations ( unsigned int OptimizerMaximumIterations )
{
    matcher->SetOptimizerMaximumIterations ( OptimizerMaximumIterations );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetHistogramSize ( unsigned int HistogramSize )
{
    matcher->SetHistogramSize ( HistogramSize );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSearchRadius ( double SearchRadius )
{
    matcher->SetSearchRadius ( SearchRadius );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSearchAngleRadius ( double SearchAngleRadius )
{
    matcher->SetSearchAngleRadius ( SearchAngleRadius );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSearchSkewRadius ( double SearchSkewRadius )
{
    matcher->SetSearchSkewRadius ( SearchSkewRadius );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSearchScaleRadius ( double SearchScaleRadius )
{
    matcher->SetSearchScaleRadius ( SearchScaleRadius );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetFinalRadius ( double FinalRadius )
{
    matcher->SetFinalRadius ( FinalRadius );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetStepSize ( double StepSize )
{
    matcher->SetStepSize ( StepSize );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetTranlateUpperBound ( double TranlateUpperBound )
{
    matcher->SetTranlateUpperBound ( TranlateUpperBound );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetAngleUpperBound ( double AngleUpperBound )
{
    matcher->SetAngleUpperBound ( AngleUpperBound );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSkewUpperBound ( double SkewUpperBound )
{
    matcher->SetSkewUpperBound ( SkewUpperBound );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetScaleUpperBound ( double ScaleUpperBound )
{
    matcher->SetScaleUpperBound ( ScaleUpperBound );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetAgregator ( unsigned int agregator )
{
    matcher->SetAgregator ( ( Agregator ) agregator );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetWeightedAgregation ( bool WeightedAgregation )
{
    matcher->SetWeightedAgregation ( WeightedAgregation );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetBlockCenteredRotations ( bool BlockCenteredRotations )
{
    matcher->SetBlockCenteredRotations ( BlockCenteredRotations );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetOutputTransformType ( unsigned int outputTransform )
{
    matcher->SetOutputTransformType ( ( OutputTransform ) outputTransform );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetAgregThreshold ( float AgregThreshold )
{
    matcher->SetAgregThreshold ( AgregThreshold );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetSeStoppingThreshold ( float SeStoppingThreshold )
{
    matcher->SetSeStoppingThreshold ( SeStoppingThreshold );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetNumberOfPyramidLevels ( unsigned int NumberOfPyramidLevels )
{
    matcher->SetNumberOfPyramidLevels ( NumberOfPyramidLevels );
}
    
    template < class TFixedImage, class TMovingImage, class TTransformScalarType >
    unsigned int AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
    ::GetNumberOfPyramidLevels ()
    {
        return matcher->GetNumberOfPyramidLevels ();
    }

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetLastPyramidLevel ( unsigned int LastPyramidLevel )
{
    matcher->SetLastPyramidLevel ( LastPyramidLevel );
}

template < class TFixedImage, class TMovingImage, class TTransformScalarType >
void AnimaPyramidalBMRegistration< TFixedImage, TMovingImage, TTransformScalarType >
::SetNumberOfThreads ( int numberOfThreads )
{
    matcher->SetNumberOfThreads ( numberOfThreads );
}

} // End of namespace
