#include "qtshanoirDataSource.h"
#include "qtshanoirDataSourceToolBox.h"
#include <QtShanoirSearchWidget.h>
#include <QtShanoir.h>

#include <medPluginManager.h>

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
	findButton->setToolTip(tr("Launch search"));
	QPushButton * downloadButton = new QPushButton("Import", this);
	downloadButton->setIcon(QIcon(":/icons/download.png"));
	downloadButton->setToolTip(tr("Import the selected data"));
  	
	QObject::connect(findButton, SIGNAL(clicked()), this, SIGNAL(findButtonPressed()));
	QObject::connect(downloadButton, SIGNAL(clicked()), this, SIGNAL(importButtonPressed()));
	
	QVBoxLayout *shanoirToolboxLayout = new QVBoxLayout(widget);
  
  QtShanoirSearchWidget *searchWidget = new QtShanoirSearchWidget;
	shanoirToolboxLayout->addWidget(searchWidget);
  
	shanoirToolboxLayout->addWidget(findButton);
	shanoirToolboxLayout->addWidget(downloadButton);
  
	widget->setLayout(shanoirToolboxLayout);
	
	this->addWidget(widget);
	this->setTitle("Queries");

  // Add about plugin
  medPluginManager* pm = medPluginManager::instance();
  dtkPlugin* plugin = pm->plugin ( "qtshanoirDataSourcePlugin" );
  setAboutPluginButton ( plugin );
  setAboutPluginVisibility( true );
}

qtshanoirDataSourceToolBox::~qtshanoirDataSourceToolBox(void)
{
	delete d;	
	d = NULL;
}
