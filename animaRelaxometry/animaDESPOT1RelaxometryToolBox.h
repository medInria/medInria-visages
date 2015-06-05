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
#include <animaRelaxometryPluginExport.h>

class animaDESPOT1RelaxometryToolBoxPrivate;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaDESPOT1RelaxometryToolBox : public medFilteringAbstractToolBox
{
    Q_OBJECT
    MED_TOOLBOX_INTERFACE("DESPOT1 Relaxometry",
                          "T1 relaxometry from 2 images",
                          << "filtering")
    
public:
    animaDESPOT1RelaxometryToolBox(QWidget *parent = 0);
    ~animaDESPOT1RelaxometryToolBox();
    
    medAbstractData *processOutput();
    
    static bool registered();
    dtkPlugin * plugin();

    void update(medAbstractData *data);

signals:
    void success();
    void failure();
    
public slots:
    void run();
    
private:
    animaDESPOT1RelaxometryToolBoxPrivate *d;
};


