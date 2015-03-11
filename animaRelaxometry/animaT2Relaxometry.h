/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <dtkCore/dtkAbstractProcess.h>
#include <medAbstractData.h>
#include <medAbstractImageData.h>

#include <animaRelaxometryPluginExport.h>

class animaT2RelaxometryPrivate;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaT2Relaxometry : public dtkAbstractProcess
{
    Q_OBJECT
    
public:
    animaT2Relaxometry();
    virtual ~animaT2Relaxometry();
    
    virtual QString description() const;
    
    static bool registered();

    // Parameters setting
    void setTRTime (double val);
    void setEchoSpacing (double val);
    void setUpperBoundM0(double val);
    void setUpperBoundT2(double val);
    void setBackgroundSignalThreshold (double val);
    void setNumberOfThreads(unsigned int val);
    void setT1Map(medAbstractImageData *t1Map);
    
public slots:
    
    //! Input data to the plugin is set through here
    void setInputImage(medAbstractData *data);
        
    //! Method to actually start the filter
    int update();
    
    //! The output will be available through here
    medAbstractData *output();
    
    
private:
    animaT2RelaxometryPrivate *d;
};

dtkAbstractProcess *createAnimaT2Relaxometry();


