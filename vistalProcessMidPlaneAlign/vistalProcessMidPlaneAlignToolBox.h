
#ifndef VISTALPROCESSMidPlaneAlignTOOLBOX_H
#define VISTALPROCESSMidPlaneAlignTOOLBOX_H

#include <medToolBoxFilteringCustom.h>

class vistalProcessMidPlaneAlignToolBoxPrivate;

class vistalProcessMidPlaneAlignToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessMidPlaneAlignToolBox(QWidget *parent = 0);
    ~vistalProcessMidPlaneAlignToolBox(void);

public:
    static bool registered(void);
    dtkAbstractData* processOutput();

signals:
    void success(void);
    void failure(void);

public slots:

    void run(void);

private:
    vistalProcessMidPlaneAlignToolBoxPrivate *d;
};

medToolBoxFilteringCustom *createVistalProcessMidPlaneAlignToolBox(QWidget *parent);

#endif

