#ifndef QTSHANOIRDATASOURCETOOLBOX_H
#define QTSHANOIRDATASOURCETOOLBOX_H

#include <medGui/medToolBoxSourceData.h>

class qtshanoirDataSourceToolBoxPrivate;
class medAbstractSourceDataPlugin;

class qtshanoirDataSourceToolBox : public medToolBoxSourceData
{
	Q_OBJECT
	
public:
	qtshanoirDataSourceToolBox(QWidget *parent = 0);
	~qtshanoirDataSourceToolBox(void);
	
	virtual medAbstractSourceDataPlugin *plugin();
	
public:
	static bool registered(void);

private:
	qtshanoirDataSourceToolBoxPrivate *d;
};

medToolBoxSourceData *createqtshanoirDataSourceToolBox(void);

#endif
