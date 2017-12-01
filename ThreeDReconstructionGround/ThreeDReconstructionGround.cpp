#include "ThreeDReconstructionGround.h"
#include "Global.h"

ThreeDReconstructionGround::ThreeDReconstructionGround(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	decodeCam1 = new DecoderThread(FILE_PATH_CAM1);
	decodeCam2 = new DecoderThread(FILE_PATH_CAM2);

	connect((const QObject*)(decodeCam1), SIGNAL(RefreshPicture(QPixmap)), (const QObject*)this, SLOT(showLable1(QPixmap)));
	connect((const QObject*)(decodeCam2), SIGNAL(RefreshPicture(QPixmap)), (const QObject*)this, SLOT(showLable2(QPixmap)));
}

void ThreeDReconstructionGround::button1Click()
{
	
	decodeCam1->start();
	decodeCam2->start();
}

void ThreeDReconstructionGround::button2Click()
{

}

void ThreeDReconstructionGround::showLable1(QPixmap pix)
{
	ui.label1->setPixmap(pix);
}

void ThreeDReconstructionGround::showLable2(QPixmap pix)
{
	ui.label2->setPixmap(pix);
}