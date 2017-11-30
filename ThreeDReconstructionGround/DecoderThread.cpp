#include "DecoderThread.h"


DecoderThread::DecoderThread(char* filePath, Ui::ThreeDReconstructionGroundClass* pUi)
{
	this->filePath = filePath;
	this->pUi = pUi;
}

DecoderThread::~DecoderThread()
{

}

void DecoderThread::run()
{
	DecoderInit();
}

int DecoderThread::DecoderInit()
{
	int ret = 0;
	int got_picture = 0;

	av_register_all();
	avformat_network_init();

	pFormatCtx = avformat_alloc_context();

	if (avformat_open_input(&pFormatCtx, filePath, NULL, NULL) != 0)
	{
		printf("Couldn't open input stream.\n");
		exit(1);
	}

	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		printf("Couldn't find stream information.\n");
		exit(1);
	}

	videoindex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex = i;
			break;
		}

	if (videoindex == -1) {
		printf("Didn't find a video stream.\n");
		exit(1);
	}

	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		exit(1);
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec.\n");
		exit(1);
	}

	pFrameRaw = av_frame_alloc();
	pFrameRGB = av_frame_alloc();
	out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height, 1));
	av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, out_buffer,
		AV_PIX_FMT_RGB32, pCodecCtx->width, pCodecCtx->height, 1);

	pPkt = (AVPacket *)av_malloc(sizeof(AVPacket));

	rawToRGB32 = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB32, SWS_BILINEAR, NULL, NULL, NULL);

	//Output Info-----------------------------  
	printf("--------------- File Information ----------------\n");
	av_dump_format(pFormatCtx, 0, filePath, 0);
	printf("-------------------------------------------------\n");

	while (av_read_frame(pFormatCtx, pPkt) >= 0)
	{
		if (pPkt->stream_index == videoindex)
		{
			ret = avcodec_decode_video2(pCodecCtx, pFrameRaw, &got_picture, pPkt);
			if (ret < 0)
			{
				printf("Decode Error.\n");
				exit(1);
				//return -1;
			}

			if (got_picture)
			{
				sws_scale(rawToRGB32, (const uchar* const*)pFrameRaw->data, pFrameRaw->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

				QImage image((uchar *)pFrameRGB->data[0], pCodecCtx->width, pCodecCtx->height, QImage::Format_RGB32);
				QPixmap pix;
				pix.convertFromImage(image);
				pUi->label1->setPixmap(pix);

				Delay_MSec(10);
			}
		}
		//av_free_packet(packet);
	}

	return 0;
}