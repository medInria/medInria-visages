#pragma once

#include <medSegmentationAbstractToolBox.h>
#include <medDataIndex.h>

class vistalProcessSegmentationGCEMToolBoxPrivate;

class vistalProcessSegmentationGCEMToolBox : public medSegmentationAbstractToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("GCEM segmentation", "GCEM lesions segmentation",
                          <<"segmentation")

public:
     vistalProcessSegmentationGCEMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationGCEMToolBox(void);

    static bool registered();

    dtkPlugin* plugin();

    medAbstractData* processOutput();

public slots:

    void onT1ImageDropped(const medDataIndex &index);
    void onPDImageDropped(const medDataIndex &index);
    void onT2orFLAIRImageDropped(const medDataIndex &index);

    void onMaskImageDropped(const medDataIndex &index);

    void run(void);

private:
    vistalProcessSegmentationGCEMToolBoxPrivate *d;
};
