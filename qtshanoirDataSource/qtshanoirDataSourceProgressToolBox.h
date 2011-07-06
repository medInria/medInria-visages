#ifndef QTSHANOIRDATASOURCEPROGRESSTOOLBOX_H
#define QTSHANOIRDATASOURCEPROGRESSTOOLBOX_H

#include <medGui/medToolBox.h>

class qtshanoirDataSourceProgressToolBoxPrivate;

class qtshanoirDataSourceProgressToolBox : public medToolBox
{
	Q_OBJECT
	
public:
	qtshanoirDataSourceProgressToolBox(QWidget *parent = 0);
	~qtshanoirDataSourceProgressToolBox(void);
	
public slots:
  void progressShown();
  void progressHidden();
  
private:
	qtshanoirDataSourceProgressToolBoxPrivate *d;
};

#endif
