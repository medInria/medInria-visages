
#ifndef VISTALPROCESSBIASREMOVALTOOLBOX_H
#define VISTALPROCESSBIASREMOVALTOOLBOX_H

#include <QObject>
#include <medGui/medToolBoxFilteringCustom.h>


class medToolBoxFilteringCustom;
class dtkAbstractData;
class vistalProcessBiasRemovalToolBoxPrivate;

class vistalProcessBiasRemovalToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessBiasRemovalToolBox(QWidget *parent = 0);
    ~vistalProcessBiasRemovalToolBox(void);

public:
    static bool registered(void);
    dtkAbstractData* processOutput();
   
signals:
    void success(void);
    void failure(void);
    
public slots:

    void run(void);

private:
    vistalProcessBiasRemovalToolBoxPrivate *d;
};

medToolBoxFilteringCustom *createVistalProcessBiasRemovalToolBox(QWidget *parent);

#endif

