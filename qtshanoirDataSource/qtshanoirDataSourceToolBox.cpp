#include "qtshanoirDataSource.h"
#include "qtshanoirDataSourceToolBox.h"

#include <medCore/medAbstractDataSource.h>
#include <medCore/medAbstractDataSourceFactory.h>
#include <QtGui>

class qtshanoirDataSourceToolBoxPrivate
{
public:
	QWidget *parent;
};

qtshanoirDataSourceToolBox::qtshanoirDataSourceToolBox(QWidget *parent) : medToolBox(parent), d(new qtshanoirDataSourceToolBoxPrivate)
{
	// Parameters:
	d->parent = parent;
	
  QWidget *widget = new QWidget(this);
	
	QPushButton * findButton = new QPushButton("Find", this);
	findButton->setIcon(QIcon(":/icons/zoom.png"));
	QPushButton * downloadButton = new QPushButton("Import", this);
	downloadButton->setIcon(QIcon(":/icons/download.png"));
	
	QObject::connect(findButton, SIGNAL(clicked()), this, SIGNAL(findButtonPressed()));
	QObject::connect(downloadButton, SIGNAL(clicked()), this, SIGNAL(importButtonPressed()));
	
	QVBoxLayout *shanoirToolboxLayout = new QVBoxLayout(widget);
	shanoirToolboxLayout->addWidget(findButton);
	shanoirToolboxLayout->addWidget(downloadButton);
  
	widget->setLayout(shanoirToolboxLayout);
	
	this->addWidget(widget);
	this->setTitle("Queries");
	
}

qtshanoirDataSourceToolBox::~qtshanoirDataSourceToolBox(void)
{
	delete d;	
	d = NULL;
}
