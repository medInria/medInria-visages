#include "qtshanoirDataSource.h"
#include "qtshanoirDataSourceProgressToolBox.h"
#include <QtShanoirProgressWidget.h>
#include <QtShanoir.h>

#include <medCore/medAbstractDataSource.h>
#include <medCore/medAbstractDataSourceFactory.h>

#include <QtGui>

class qtshanoirDataSourceProgressToolBoxPrivate
{
public:
	QWidget *parent;
  QtShanoirProgressWidget *progressWidget;
};

qtshanoirDataSourceProgressToolBox::qtshanoirDataSourceProgressToolBox(QWidget *parent) : medToolBox(parent), d(new qtshanoirDataSourceProgressToolBoxPrivate)
{
	// Parameters:
	d->parent = parent;
  d->progressWidget = NULL;
	
  QWidget *widget = new QWidget(this);
	
	QVBoxLayout *toolboxLayout = new QVBoxLayout(widget);
  
	if(!d->progressWidget)
    d->progressWidget = new QtShanoirProgressWidget();

	toolboxLayout->addWidget(d->progressWidget);
  
  QtShanoir::instance()->attachProgressWidget(d->progressWidget);
  connect(QtShanoir::instance(),SIGNAL(progressHidden()),this,SLOT(progressHidden()));
  connect(QtShanoir::instance(),SIGNAL(progressShown()),this,SLOT(progressShown()));

	widget->setLayout(toolboxLayout);
	
	this->addWidget(widget);
	this->setTitle("Progress");
  this->progressHidden();
}

void qtshanoirDataSourceProgressToolBox::progressHidden(void)
{
	this->hide();
}

void qtshanoirDataSourceProgressToolBox::progressShown(void)
{
	this->show();
}

qtshanoirDataSourceProgressToolBox::~qtshanoirDataSourceProgressToolBox(void)
{
	delete d;	
	d = NULL;
}
