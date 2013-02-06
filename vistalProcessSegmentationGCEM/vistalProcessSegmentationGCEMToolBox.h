
#ifndef VISTALPROCESSSegmentationGCEMTOOLBOX_H
#define VISTALPROCESSSegmentationGCEMTOOLBOX_H

#include <medToolBoxSegmentationCustom.h>
#include <medDataIndex.h>

class vistalProcessSegmentationGCEMToolBoxPrivate;

class vistalProcessSegmentationGCEMToolBox : public medToolBoxSegmentationCustom
{
    Q_OBJECT

public:
     vistalProcessSegmentationGCEMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationGCEMToolBox(void);

public:
    static bool registered(void);

public slots:

    void onT1ImageDropped(const medDataIndex &index);
    void onPDImageDropped(const medDataIndex &index);
    void onT2orFLAIRImageDropped(const medDataIndex &index);

    void onMaskImageDropped(const medDataIndex &index);

    void run(void);

private:
    vistalProcessSegmentationGCEMToolBoxPrivate *d;
};

#endif

