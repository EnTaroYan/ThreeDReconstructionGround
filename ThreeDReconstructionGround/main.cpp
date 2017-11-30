#include "ThreeDReconstructionGround.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ThreeDReconstructionGround w;
	w.show();
	return a.exec();
}
