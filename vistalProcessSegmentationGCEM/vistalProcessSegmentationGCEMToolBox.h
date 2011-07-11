
#ifndef VISTALPROCESSSegmentationGCEMTOOLBOX_H
#define VISTALPROCESSSegmentationGCEMTOOLBOX_H

#include <medGui/medToolBoxFilteringCustom.h>

class vistalProcessSegmentationGCEMToolBoxPrivate;

class vistalProcessSegmentationGCEMToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessSegmentationGCEMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationGCEMToolBox(void);

public:
    static bool registered(void);
    dtkAbstractData* processOutput();

signals:
    void success(void);
    void failure(void);

public slots:

    void onT1ImageDropped(void);
    void onPDImageDropped(void);
    void onT2orFLAIRImageDropped(void);

    void onMaskImageDropped(void);

    void run(void);

private:
    vistalProcessSegmentationGCEMToolBoxPrivate *d;
};

medToolBoxFilteringCustom *createVistalProcessSegmentationGCEMToolBox(QWidget *parent);

#endif

