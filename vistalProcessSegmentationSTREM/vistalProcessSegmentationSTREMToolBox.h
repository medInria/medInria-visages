
#ifndef VISTALPROCESSSegmentationSTREMTOOLBOX_H
#define VISTALPROCESSSegmentationSTREMTOOLBOX_H

#include <medDataIndex.h>
#include <medSegmentationAbstractToolBox.h>

class vistalProcessSegmentationSTREMToolBoxPrivate;

class vistalProcessSegmentationSTREMToolBox : public medSegmentationAbstractToolBox
{
    Q_OBJECT

public:
     vistalProcessSegmentationSTREMToolBox(QWidget *parent = 0);
    ~vistalProcessSegmentationSTREMToolBox(void);

public:
    static bool registered(void);

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

