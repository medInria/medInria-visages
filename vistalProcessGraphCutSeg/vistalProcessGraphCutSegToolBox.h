#ifndef VISTALPROCESSGRAPHCUTSEGTOOLBOX_H
#define VISTALPROCESSGRAPHCUTSEGTOOLBOX_H

#include <medToolBoxSegmentationCustom.h>

class vistalProcessGraphCutSegToolBoxPrivate;

class vistalProcessGraphCutSegToolBox : public medToolBoxSegmentationCustom
{
    Q_OBJECT

public:

    vistalProcessGraphCutSegToolBox(QWidget *parent = 0);
    ~vistalProcessGraphCutSegToolBox();

public:

    static bool registered();

private slots:
    void onMultipleImageSelectionClicked();
    void run();

private:
    vistalProcessGraphCutSegToolBoxPrivate *d;
};

#endif