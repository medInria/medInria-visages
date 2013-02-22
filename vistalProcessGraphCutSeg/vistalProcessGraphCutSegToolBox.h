#ifndef VISTALPROCESSGRAPHCUTSEGTOOLBOX_H
#define VISTALPROCESSGRAPHCUTSEGTOOLBOX_H

#include <medSegmentationAbstractToolBox.h>
#include <medDataIndex.h>

class vistalProcessGraphCutSegToolBoxPrivate;

class vistalProcessGraphCutSegToolBox : public medSegmentationAbstractToolBox
{
    Q_OBJECT

public:

    vistalProcessGraphCutSegToolBox(QWidget *parent = 0);
    ~vistalProcessGraphCutSegToolBox();

public:

    static bool registered();

private slots:
    void onMultipleImageSelectionClicked();
    void onMaskDropped(const medDataIndex& index);
    void run();

private:
    vistalProcessGraphCutSegToolBoxPrivate *d;
};

#endif
