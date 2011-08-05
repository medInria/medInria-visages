#ifndef QTSHANOIRDATASOURCETOOLBOX_H
#define QTSHANOIRDATASOURCETOOLBOX_H

#include <medToolBox.h>

class qtshanoirDataSourceToolBoxPrivate;

class qtshanoirDataSourceToolBox : public medToolBox
{
	Q_OBJECT
	
public:
	qtshanoirDataSourceToolBox(QWidget *parent = 0);
	~qtshanoirDataSourceToolBox(void);
	
signals:
  void importButtonPressed(void);
  void findButtonPressed(void);
  
private:
	qtshanoirDataSourceToolBoxPrivate *d;
};

#endif
