#include "qtshanoirDataSource.h"
#include "qtshanoirDataSourceToolBox.h"

#include <medGui/medToolBoxFactory.h>
#include <medGui/medToolBoxSourceData.h>
#include <medCore/medAbstractSourceDataPlugin.h>
#include <medCore/medSourceDataPluginFactory.h>
#include <QtGui>

class qtshanoirDataSourceToolBoxPrivate
{
public:
	medAbstractSourceDataPlugin *data_source;
	QWidget *parent;
};

qtshanoirDataSourceToolBox::qtshanoirDataSourceToolBox(QWidget *parent) : medToolBoxSourceData(parent), d(new qtshanoirDataSourceToolBoxPrivate)
{
	// Parameters:
	d->data_source = NULL;
	d->parent = parent;
	
        QWidget *widget = new QWidget(this);
	
	QPushButton * findButton = new QPushButton("Find", this);
	findButton->setIcon(QIcon(":/icons/zoom.png"));
	QPushButton * downloadButton = new QPushButton("Import", this);
	downloadButton->setIcon(QIcon(":/icons/download.png"));
	
	QObject::connect(findButton, SIGNAL(clicked()), this->plugin(), SLOT(find()));
	QObject::connect(downloadButton, SIGNAL(clicked()), this->plugin(), SLOT(onImportData()));
	
	QVBoxLayout *shanoirToolboxLayout = new QVBoxLayout(widget);
	shanoirToolboxLayout->addWidget(findButton);
	shanoirToolboxLayout->addWidget(downloadButton);

	widget->setLayout(shanoirToolboxLayout);
	
	this->addWidget(widget);
	this->setTitle("Queries");
	
}

qtshanoirDataSourceToolBox::~qtshanoirDataSourceToolBox(void)
{
	if (d->data_source)
		delete d->data_source;
	
	delete d;
	
	d = NULL;
}

bool qtshanoirDataSourceToolBox::registered(void)
{
	return medToolBoxFactory::instance()->registerSourceDataToolBox("qtshanoirDataSourceToolBox",createqtshanoirDataSourceToolBox);
}

medAbstractSourceDataPlugin *qtshanoirDataSourceToolBox::plugin()
{
	if (!d->data_source)
		d->data_source = medSourceDataPluginFactory::instance()->create("qtshanoirDataSource");

	return d->data_source;
}

medToolBoxSourceData *createqtshanoirDataSourceToolBox(void)
{
	return new qtshanoirDataSourceToolBox;
}