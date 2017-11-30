#pragma once

#include "ui_ThreeDReconstructionGround.h"
#include <stdio.h>
#include <QThread>
#include <Global.h>
#include <string.h>
#include <QImage>
#include <QString>
#include <QPixmap>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

class DecoderThread :QThread
{
public:
	DecoderThread(char* filePath, Ui::ThreeDReconstructionGroundClass* pUi);
	~DecoderThread();
	virtual void run();
	int DecoderInit();

private:
	Ui::ThreeDReconstructionGroundClass* pUi;

	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrameRaw, *pFrameRGB;
	AVPacket *pPkt;
	struct SwsContext *rawToRGB32;
	unsigned char *out_buffer;
	char* filePath;
	int	videoindex;
};