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
	DecoderThread(char* filePath);
	~DecoderThread();
	virtual void run();
	int DecoderInit();

private:
	QLabel* showLable;

	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrameRaw, *pFrameRGB;
	AVPacket *pPkt;
	struct SwsContext *rawToRGB32;
	unsigned char *out_buffer;
	char* filePath;
	int	videoindex;

signals:
	void RefreshPicture(QPixmap);
};