#pragma once

#include <medAbstractSymmetryPlaneAlignmentProcess.h>
#include <medAbstractData.h>

#include <itkProcessObject.h>
#include <itkSmartPointer.h>
#include <itkAffineTransform.h>

#include "animaSymmetryPlanePluginExport.h"
#include <medIntParameter.h>
#include <medDoubleParameter.h>

class ANIMASYMMETRYPLANEPLUGIN_EXPORT animaSymmetryPlaneProcess : public medAbstractSymmetryPlaneAlignmentProcess
{
    Q_OBJECT

public:
    typedef itk::AffineTransform<double,3> TransformType;
    typedef TransformType::Pointer TransformPointer;

    animaSymmetryPlaneProcess(QObject* parent = NULL);
    virtual ~animaSymmetryPlaneProcess();

    static void eventCallback(itk::Object *caller, const itk::EventObject& event, void *clientData)
    {
        medAbstractSymmetryPlaneAlignmentProcess * source = reinterpret_cast<medAbstractSymmetryPlaneAlignmentProcess *>(clientData);
        itk::ProcessObject * processObject = (itk::ProcessObject*) caller;
        source->progression()->setValue(processObject->GetProgress() * 100);
    }

    virtual medAbstractJob::medJobExitStatus run();
    virtual void cancel();

    virtual QString caption() const;
    virtual QString description() const;
    
    // Parameters setting
    int metric() const;
    medIntParameter *optimizerMaximumIterations() const;
    medIntParameter *histogramSize() const;
    medIntParameter *pyramidLevelsNumber() const;

    medDoubleParameter *upperBoundAngle() const;
    medDoubleParameter *upperBoundDistance() const;

    TransformPointer &outputRealignTransform();

public slots:
    void setMetric(int value);

private:
    template <class PixelType> medAbstractJob::medJobExitStatus _run();

    itk::SmartPointer<itk::ProcessObject> m_symmetryplanebridge;
    int m_Metric;
    medIntParameter *m_optimizerMaximumIterations;
    medIntParameter *m_histogramSize;
    medIntParameter *m_pyramidLevelsNumber;

    medDoubleParameter *m_upperBoundAngle;
    medDoubleParameter *m_upperBoundDistance;

    TransformPointer m_outputRealignTransform;
};

inline medAbstractSymmetryPlaneAlignmentProcess* animaSymmetryPlaneProcessCreator()
{
    return new animaSymmetryPlaneProcess();
}
