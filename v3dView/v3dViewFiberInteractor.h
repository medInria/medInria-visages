#ifndef V3DVIEWFIBERINTERACTOR_H
#define V3DVIEWFIBERINTERACTOR_H

#include <dtkCore/dtkAbstractViewInteractor.h>

#include "v3dViewPluginExport.h"

class v3dViewFiberInteractorPrivate;

class dtkAbstractData;
class dtkAbstractView;

class V3DVIEWPLUGIN_EXPORT v3dViewFiberInteractor: public dtkAbstractViewInteractor
{

	Q_OBJECT
	
public:
	v3dViewFiberInteractor();
	virtual ~v3dViewFiberInteractor();
	
	virtual QString description(void) const;
	virtual QStringList handled(void) const;
	
	static bool registered(void);
	
	virtual void setData(dtkAbstractData *data);
	virtual void setView(dtkAbstractView *view);
	
public slots:
    virtual void onPropertySet (QString key, QString value);
	virtual void onVisibilityPropertySet (QString value);
	virtual void onBoxVisibilityPropertySet (QString value);
	virtual void onRenderingModePropertySet (QString value);
	virtual void onGPUModePropertySet (QString value);
	virtual void onColorModePropertySet (QString value);
	virtual void onBoxBooleanOperationPropertySet (QString value);
	virtual void onProjectionPropertySet (QString value);
	
	virtual void onSelectionTagged (void);
    virtual void onSelectionReset (void);
/*
    virtual void onBundleValidated (void);
    virtual void onBundleClicked (QListWidgetItem* item);
    virtual void onBundleVisibilityClicked (bool value);
    virtual void onBundleColorModeClicked (bool value);
    virtual void onShowAllClicked (bool value);
    virtual void onDeleteAllClicked (void);
    virtual void onBundleDeleteClicked (void);
    virtual void onBundleColorClicked (void);
    virtual void onBundleNameChanged (void);
*/	
private:
    v3dViewFiberInteractorPrivate *d;

};

dtkAbstractViewInteractor *createV3dViewFiberInteractor(void);

#endif