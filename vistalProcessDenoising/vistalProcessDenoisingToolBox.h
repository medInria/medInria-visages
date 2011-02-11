
#ifndef VISTALPROCESSDENOISINGTOOLBOX_H
#define VISTALPROCESSDENOISINGTOOLBOX_H

#include <medGui/medToolBoxFilteringCustom.h>

class vistalProcessDenoisingToolBoxPrivate;

class vistalProcessDenoisingToolBox : public medToolBoxFilteringCustom
{
    Q_OBJECT

public:
     vistalProcessDenoisingToolBox(QWidget *parent = 0);
    ~vistalProcessDenoisingToolBox(void);

public:
    static bool registered(void);
   
//signals:
    
public slots:

    void run(void);

//    void setSlopeType(int);
//    void setSigma(double);
//    void setBeta(double);
//    void setNeighborhoodSize(double);
//    void setSearchVolumeSize(double);
//    void setWeightingMethod(int);
//    void setNeighborhoodType(int);
//
//    void setBlockApproach(int);
//    void setTestOnMean(int);
//    void setTestOnVar(int);
//    void setMinimumMeanRatio(double);
//    void setMinimumVarRatio(double);
//    void setDistanceBetweenBlocks(int);
//    void setNumberOfThreads(unsigned int);

private:
    vistalProcessDenoisingToolBoxPrivate *d;
};

medToolBoxFilteringCustom *createVistalProcessDenoisingToolBox(void);

#endif
