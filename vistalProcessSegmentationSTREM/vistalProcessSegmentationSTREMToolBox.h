
#ifndef VISTALPROCESSSegmentationSTREMTOOLBOX_H
#define VISTALPROCESSSegmentationSTREMTOOLBOX_H

#include <medDataIndex.h>
#include <medSegmentationAbstractToolBox.h>

class vistalProcessSegmentationSTREMToolBoxPrivate;

class vistalProcessSegmentationSTREMToolBox : public medSegmentationAbstractToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("STREM segmentation", "Rob. EM based segmentation of MS lesions",
                          <<"segmentation")

public:
     vistalProcessSegmentationSTREMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationSTREMToolBox(void);

    static bool registered(void);

    dtkPlugin* plugin();

    medAbstractData* processOutput();

signals:
    void success(void);
    void failure(void);

public slots:

    void onT1ImageDropped(const medDataIndex &index);
    void onPDImageDropped(const medDataIndex &index);
    void onT2orFLAIRImageDropped(const medDataIndex &index);

    void onMaskImageDropped(const medDataIndex &index);

    void run(void);

private:
    vistalProcessSegmentationSTREMToolBoxPrivate *d;
};

#endif

