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

#include <animaRelaxometryPluginExport.h>

class animaDESPOT1RelaxometryPrivate;

class ANIMARELAXOMETRYPLUGIN_EXPORT animaDESPOT1Relaxometry : public dtkAbstractProcess
{
    Q_OBJECT
    
public:
    animaDESPOT1Relaxometry();
    virtual ~animaDESPOT1Relaxometry();
    
    virtual QString description() const;
    
    static bool registered();

    // Parameters setting
    void setTRTime (double val);
    void setFirstFlipAngle (double val);
    void setSecondFlipAngle (double val);
    void setUpperBoundM0(double val);
    void setUpperBoundT1(double val);
    void setBackgroundSignalThreshold (double val);
    void setNumberOfThreads(unsigned int val);
    
public slots:
    
    //! Input data to the plugin is set through here
    void setInputImage(medAbstractData *data);
        
    //! Method to actually start the filter
    int update();
    
    //! The output will be available through here
    medAbstractData *output();
    
    
private:
    animaDESPOT1RelaxometryPrivate *d;
};

dtkAbstractProcess *create();


