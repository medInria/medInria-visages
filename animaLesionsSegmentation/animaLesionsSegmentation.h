// /////////////////////////////////////////////////////////////////
// Generated by medPluginGenerator
// /////////////////////////////////////////////////////////////////

#pragma once

#include <dtkCore/dtkAbstractProcess.h>
#include <medAbstractData.h>
#include <medAbstractImageData.h>
#include <medAbstractSegmentationProcess.h>
#include <itkImageFileReader.h>
#include "animaLesionsSegmentationPluginExport.h"


class animaLesionsSegmentationPrivate;

class ANIMALESIONSSEGMENTATIONPLUGIN_EXPORT animaLesionsSegmentation : public medAbstractSegmentationProcess
{
    Q_OBJECT

public:
    animaLesionsSegmentation(void);
    virtual ~animaLesionsSegmentation(void);

    virtual QString description(void) const;//

    //void emitProgressed(int progression);

    QList<medAbstractParameter*> parameters();

    QWidget* parameterWidget();

    bool isInteractive();

    //virtual medToolBox* toolbox();

    static bool registered(void);
    itk::Image <float,3>::Pointer createInputImages(medAbstractImageData *data);
    itk::Image <unsigned char,3>::Pointer createInputMasks(medAbstractImageData *medInput);

    virtual medViewContainerSplitter* viewContainerSplitter();

    void setDataInContainer(medAbstractData *medInput, int &pos, QString mod);
    void checkNbSequences();
    void removeSeq(int &pos);

public slots:
    void run();
    //! Input data to the plugin is set through here
    //void setInputImage(medAbstractData *data);

    //! Method to actually start the filter
    int update(void);

    //! The output will be available through here
    //medAbstractData *output(void);

    void onClearImagesClicked();    
    void onClearManuSegMaskClicked();
    void onClearExternalMaskClicked();

    void displayOutputs();
    void displayWarnings();

    void onMaskDropped(const medDataIndex& index);
    void onT1Dropped(const medDataIndex& index);
    void onT2Dropped(const medDataIndex& index);
    void onDPDropped(const medDataIndex& index);
    void onFLAIRDropped(const medDataIndex& index);
    void onT1GdDropped(const medDataIndex& index);

    void onManuSegMaskDropped(const medDataIndex& index);
    void onExternalMaskDropped(const medDataIndex& index);

    void chooseT1changed(bool state);
    void chooseT2changed(bool state);
    void chooseDPchanged(bool state);
    void chooseFLAIRchanged(bool state);
    void chooseT1Gdchanged(bool state);


    void ChangeAutomaticState(bool);
    void ChangeManuState(bool);
    void CheckedStrem(bool);
    void CheckedFuzzy(bool);
    void updateRejectionFeatures(int);
    void ChangedIntensityState(bool);

    void currentLayerChangedSlot();
    void viewChangedSlot();
    void viewContentChangedSlotView1();
    void viewContentChangedSlotView2();
    void viewContentChangedSlotView3();


private:
    animaLesionsSegmentationPrivate *d;
};

dtkAbstractProcess *createanimaLesionsSegmentation(void);
