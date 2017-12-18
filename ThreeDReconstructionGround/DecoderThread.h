#pragma once

#include "ui_ThreeDReconstructionGround.h"
#include <stdio.h>
#include <QThread>
#include <Global.h>
#include <string.h>
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QObject>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

class DecoderThread :public QThread
{
	Q_OBJECT

public:
	DecoderThread(char* filePath,char *camNumber);
	~DecoderThread();
	virtual void run();
	int DecoderInit();

private:
	QLabel* showLable;

	char* camNumber;

	//decode video
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrameRaw, *pFrameRGB;
	AVPacket *pPkt;
	struct SwsContext *rawToRGB32;
	unsigned char *out_buffer;
	char* filePath;
	int	videoindex;

	//encode jpg picture
	int SaveAsJPEG(char* filename, AVFrame* pFrame, int width, int height);

signals:
	void RefreshPicture(QPixmap);
};