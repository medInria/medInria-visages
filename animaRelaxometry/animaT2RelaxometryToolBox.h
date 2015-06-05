/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medFilteringAbstractToolBox.h>
#include <medDataIndex.h>
#include <animaRelaxometryPluginExport.h>

class animaT2RelaxometryToolBoxPrivate;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaT2RelaxometryToolBox : public medFilteringAbstractToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("T2 Relaxometry",
                          "T2 relaxometry from a series of N images",
                          << "filtering")
    
public:
    animaT2RelaxometryToolBox(QWidget *parent = 0);
    ~animaT2RelaxometryToolBox();
    
    medAbstractData *processOutput();
    
    static bool registered();
    dtkPlugin * plugin();

    void update(medAbstractData *data);

signals:
    void success();
    void failure();
    
public slots:
    void setT1Map(const medDataIndex &index);
    void run();
    
private:
    animaT2RelaxometryToolBoxPrivate *d;
};


