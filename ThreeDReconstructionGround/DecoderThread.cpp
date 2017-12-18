#include "DecoderThread.h"
#include "Global.h"

DecoderThread::DecoderThread(char* filePath, char *camNumber)
{
	this->filePath = filePath;
	this->camNumber = camNumber;
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

	//printf("start\n");

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

	/*pCodec = avcodec_find_encoder_by_name("h264_qsv");
	if (pCodec == NULL) {
		printf("Codec not found.\n");
		exit(1);
	}

	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx) {
		printf("Could not open codec.\n");
		exit(1);
	}
	pCodecCtx->bit_rate = 1000000;
	pCodecCtx->width = 640;
	pCodecCtx->height = 480;
	pCodecCtx->time_base.den = 1;
	pCodecCtx->time_base.num = 25;
	pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

	if (avcodec_open2(pCodecCtx, pCodec, NULL))
	{
		printf("could not open codec context");
		exit(1);
	}*/

	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) 
	{
		printf("Codec not found.\n");
		exit(1);
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) 
	{
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
				emit RefreshPicture(pix);
				int number = pFrameRaw->pts;
				char a[50];
				sprintf(a, "%s%d",camNumber, number);
				SaveAsJPEG(a, pFrameRaw, pCodecCtx->width, pCodecCtx->height);
				//showLable->setPixmap(pix);

				printf("%d \n", (int)pFrameRaw->pts);
				Delay_MSec(10);
			}
		}
		//av_free_packet(packet);
	}

	return 0;
}

int DecoderThread::SaveAsJPEG(char* filename,AVFrame* pFrameImg, int width, int height)
{
	// 输出文件路径  
	char out_file[50];
	sprintf(out_file, "%s%s.jpg", PICTURE_PATH, filename);

	// 分配AVFormatContext对象  
	AVFormatContext* pFormatImgCtx = avformat_alloc_context();

	// 设置输出文件格式  
	pFormatImgCtx->oformat = av_guess_format("mjpeg", NULL, NULL);
	// 创建并初始化一个和该url相关的AVIOContext  
	if (avio_open(&pFormatImgCtx->pb, out_file, AVIO_FLAG_READ_WRITE) < 0) {
		printf("Couldn't open output file.");
		return -1;
	}

	// 构建一个新stream  
	AVStream* pStreamImg = avformat_new_stream(pFormatImgCtx, 0);
	if (pStreamImg == NULL) {
		return -1;
	}

	// 设置该stream的信息  
	AVCodecContext* pCodecImgCtx = pStreamImg->codec;

	pCodecImgCtx->codec_id = pFormatImgCtx->oformat->video_codec;
	pCodecImgCtx->codec_type = AVMEDIA_TYPE_VIDEO;
	pCodecImgCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
	pCodecImgCtx->width = width;
	pCodecImgCtx->height = height;
	pCodecImgCtx->time_base.num = 1;
	pCodecImgCtx->time_base.den = 30;

	// 查找解码器  
	AVCodec* pCodecImg = avcodec_find_encoder(pCodecImgCtx->codec_id);
	if (!pCodecImg) {
		printf("Codec not found.");
		return -1;
	}
	// 设置pCodecCtx的解码器为pCodec  
	if (avcodec_open2(pCodecImgCtx, pCodecImg, NULL) < 0) {
		printf("Could not open codec.");
		return -1;
	}

	//Write Header  
	avformat_write_header(pFormatImgCtx, NULL);

	int y_size = pCodecImgCtx->width * pCodecImgCtx->height;

	//Encode  
	// 给AVPacket分配足够大的空间  
	AVPacket pktImg;
	av_new_packet(&pktImg, y_size * 3);

	//   
	int got_picture = 0;
	int ret = avcodec_encode_video2(pCodecImgCtx, &pktImg, pFrameImg, &got_picture);
	if (ret < 0) {
		printf("Encode Error.\n");
		return -1;
	}
	if (got_picture == 1) {
		//pkt.stream_index = pAVStream->index;  
		ret = av_write_frame(pFormatImgCtx, &pktImg);
	}

	av_free_packet(&pktImg);

	//Write Trailer  
	av_write_trailer(pFormatImgCtx);

	printf("Encode Successful.\n");

	if (pStreamImg) {
		avcodec_close(pStreamImg->codec);
	}
	avio_close(pFormatImgCtx->pb);
	avformat_free_context(pFormatImgCtx);

	return 0;
}