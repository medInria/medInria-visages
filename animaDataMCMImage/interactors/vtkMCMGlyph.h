/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <vtkPolyDataAlgorithm.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>

#include <vtkMCMSource.h>

#include <animaDataMCMImagePluginExport.h>

class ANIMADATAMCMIMAGEPLUGIN_EXPORT vtkMCMGlyph : public vtkPolyDataAlgorithm
{
public:   
    vtkTypeRevisionMacro(vtkMCMGlyph,vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os,vtkIndent indent);

    /** Construct object with scale factor 1.0. */
    static vtkMCMGlyph* New();

    /** Specify the geometry to copy to each point. Old style. See SetSourceConnection.*/
    void SetSource(vtkPolyData* source) { this->SetInput(1,source); }
    vtkPolyData *GetSource();

    /** Specify the MCM Source that the glyph needs to draw a deform
     *  spherical function at every point.*/
    void SetMCMSource(vtkMCMSource* mcm) { this->MCMSource = mcm; mcm->Register(this);}

    static const char* GetMCMCoefficientsArrayName() { return "mcm_coeff"; }
    static const char* GetRGBArrayName() { return "rgb"; }

    /** Specify a source object at a specified table location. New style. Source
     *  connection is stored in port 1. This method is equivalent to
     *  SetInputConnection(1,id,outputPort).*/
    void SetSourceConnection(int id,vtkAlgorithmOutput* algOutput);
    void SetSourceConnection(vtkAlgorithmOutput* algOutput) { this->SetSourceConnection(0,algOutput); }

    /** Specify scale factor to scale object by. (Scale factor always affects
     *  output even if scaling is off.)*/
    vtkSetMacro(ScaleFactor,double);
    vtkGetMacro(ScaleFactor,double);

    /** Get/set the transformation matrix that is used to display the glyphs
     *  according to the image coordinate system*/

    vtkSetObjectMacro(TMatrix,vtkMatrix4x4);
    vtkGetObjectMacro(TMatrix,vtkMatrix4x4);

protected:
    vtkMCMGlyph();
    ~vtkMCMGlyph();

    virtual int RequestData(vtkInformation*,vtkInformationVector**,vtkInformationVector*);
    virtual int FillInputPortInformation(int port,vtkInformation *info);

    // Scale factor to use to scale geometry
    double ScaleFactor;

    vtkMCMSource *MCMSource;
    vtkMatrix4x4 *TMatrix;

private:
    vtkMCMGlyph(const vtkMCMGlyph&);  // Not implemented.
    void operator=(const vtkMCMGlyph&);  // Not implemented.

    bool isZero(double* mcm, unsigned int size);
};
