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
	
public:
	static bool registered(void);

signals:
  void importButtonPressed(void);
  void findButtonPressed(void);
  
private:
	qtshanoirDataSourceToolBoxPrivate *d;
};

medToolBoxSourceData *createqtshanoirDataSourceToolBox(void);

#endif
