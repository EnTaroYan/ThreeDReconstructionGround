#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ThreeDReconstructionGround.h"
#include "DecoderThread.h"

class ThreeDReconstructionGround : public QMainWindow
{
	Q_OBJECT

public:
	ThreeDReconstructionGround(QWidget *parent = Q_NULLPTR);

private:
	Ui::ThreeDReconstructionGroundClass ui;
	DecoderThread *decodeCam1;
	DecoderThread *decodeCam2;

private slots:
	void button1Click();
	void button2Click();
};
