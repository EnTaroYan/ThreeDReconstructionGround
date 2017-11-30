#include "ThreeDReconstructionGround.h"
#include "Global.h"

ThreeDReconstructionGround::ThreeDReconstructionGround(QWidget *parent)
	: QMainWindow(parent)
{
	decodeCam1 = new DecoderThread(FILE_PATH_CAM1, &ui);
	decodeCam2 = new DecoderThread(FILE_PATH_CAM2, &ui);
	ui.setupUi(this);
}

void ThreeDReconstructionGround::button1Click()
{
	decodeCam1->run();
}

void ThreeDReconstructionGround::button2Click()
{

}