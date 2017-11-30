#include "Global.h"
#include <QtWidgets/QApplication>
#include <QTime>

void Delay_MSec(unsigned int msec)
{
	QTime _Timer = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < _Timer)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}