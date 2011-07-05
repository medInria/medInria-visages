#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

#include <QtCore>
#include <QtGui>
#include <QtDebug>

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	application.setApplicationName("vistalProcessBiasRemovalTesting");
	application.setApplicationVersion("0.0.1");
	application.setOrganizationName("INRIA");
	application.setOrganizationDomain("FR");
	
	dtkPluginManager::instance()->initialize();
		

	dtkAbstractProcess *worker = dynamic_cast <dtkAbstractProcess *>(dtkAbstractProcessFactory::instance()->create("vistalProcessBiasRemoval"));

	worker->setInput(inputImage);
	worker->setParameter(2.0,13);
	
	worker->run();
		
	dtkPluginManager::instance()->uninitialize();
	
	return DTK_SUCCEED;
}
