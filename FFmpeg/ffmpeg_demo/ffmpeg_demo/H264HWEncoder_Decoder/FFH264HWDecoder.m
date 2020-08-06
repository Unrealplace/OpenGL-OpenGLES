//
//  FFH264HWDecoder.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "FFH264HWDecoder.h"

@interface FFH264HWDecoder()

/// sps数据
@property (nonatomic, assign) uint8_t *sps;

/// sps数据长度
@property (nonatomic, assign) NSInteger spsSize;

/// pps数据
@property (nonatomic, assign) uint8_t *pps;

/// pps数据长度
@property (nonatomic, assign) NSInteger ppsSize;

/// 解码器
@property (nonatomic, assign) VTDecompressionSessionRef decoderSession;

/// 解码信息句柄
@property (nonatomic, assign) CMVideoFormatDescriptionRef decoderFormatDescription;

@end

@implementation FFH264HWDecoder

//一、硬解码名词(结构)解释
//
//1、VTDecompressionSessionRef：解码器对象数据结构；
//2、CMVideoFormatDescriptionRef：图形解码相关格式及描述；
//3、CVPixelBufferRef：编码前和解码后的图像数据结构；
//4、CMBlockBufferRef：存在解码前图像数据内存结构；
//5、CMSampleBufferRef：存放解码前的视频图像的容器数据结构；
//6、AVSampleBufferDisplayLayer：以CMSampleBufferRef进行解码并显示Layer图层；
//7、SPS、PPS：h.264解码参数信息；IDR：h.264视频流I帧；


- (void)dealloc {
    NSLog(@"%s",__func__);
    if (NULL == _decoderSession) {
        return;
    }
    CFRelease(_decoderSession);
    _decoderSession = NULL;
}


- (void)decode:(uint8_t *)frame withSize:(uint32_t)frameSize {
    // 创建 CMBlockBufferRef
    CMBlockBufferRef blockBuffer = NULL;
    OSStatus status = CMBlockBufferCreateWithMemoryBlock(NULL,
                                                         (void *)frame,
                                                         frameSize,
                                                         kCFAllocatorNull,
                                                         NULL,
                                                         0,
                                                         frameSize,
                                                         FALSE,
                                                         &blockBuffer);
    if (status != kCMBlockBufferNoErr) {
        return;
    }
    
    // 创建 CMSampleBufferRef
    CMSampleBufferRef sampleBuffer = NULL;
    const size_t sampleSizeArray[] = {frameSize};
    status = CMSampleBufferCreateReady(kCFAllocatorDefault,
                                       blockBuffer,
                                       _decoderFormatDescription,
                                       1,
                                       0,
                                       NULL,
                                       1,
                                       sampleSizeArray,
                                       &sampleBuffer);
    if (status != kCMBlockBufferNoErr || sampleBuffer == NULL) {
        return;
    }
    
    // VTDecodeFrameFlags 0为允许多线程解码
    VTDecodeFrameFlags flags = 0;
    VTDecodeInfoFlags flagOut = 0;
    // 解码 这里第四个参数会传到解码的callback里的sourceFrameRefCon，可为空
    OSStatus decodeStatus = VTDecompressionSessionDecodeFrame(_decoderSession,
                                                              sampleBuffer,
                                                              flags,
                                                              NULL,
                                                              &flagOut);
    if (decodeStatus == kVTInvalidSessionErr) {
        NSLog(@"H264Decoder::Invalid session, reset decoder session");
    } else if (decodeStatus == kVTVideoDecoderBadDataErr) {
        NSLog(@"H264Decoder::decode failed status = %d(Bad data)", (int)decodeStatus);
    } else if (decodeStatus != noErr) {
        NSLog(@"H264Decoder::decode failed status = %d", (int)decodeStatus);
    }
    // Create了就得Release
    CFRelease(sampleBuffer);
    CFRelease(blockBuffer);
    return;
}

- (void)decodeNaluData:(NSData *)naluData {
    uint8_t *frame = (uint8_t *)naluData.bytes;
    uint32_t frameSize = (uint32_t)naluData.length;

    // frame的前4位是NALU数据的开始码，也就是00 00 00 01，
    // 第5个字节是表示数据类型，转为10进制后，7是sps,8是pps,5是IDR（I帧）信息
    int nalu_type = frame[4] & 0x1F;
    
    // 将NALU的开始码替换成NALU的长度信息 uint32_t 4 字节
    uint32_t nalSize = (uint32_t)(frameSize - 4);
    uint8_t *pNalSize = (uint8_t *)(&nalSize);
    frame[0] = *(pNalSize + 3);
    frame[1] = *(pNalSize + 2);
    frame[2] = *(pNalSize + 1);
    frame[3] = *(pNalSize);
    
    switch (nalu_type) {
        case 0x05:
        {
            NSLog(@"============NALU type is IDR frame============");
            if ([self initH264Decoder]) {
                [self decode:frame withSize:frameSize];
            }

        }
            break;
        case 0x07:
        {
            NSLog(@"============NALU type is SPS frame============");
            _spsSize = frameSize - 4;
            _sps = malloc(_spsSize);
            memcpy(_sps, &frame[4], _spsSize);
        }
            break;
        case 0x08:
        {
            NSLog(@"============NALU type is PPS frame============");
            _ppsSize = frameSize - 4;
            _pps = malloc(_ppsSize);
            memcpy(_pps, &frame[4], _ppsSize);
        }
            break;
            
        default:
        {
            NSLog(@"============NALU type is B/P frame============");
            if ([self initH264Decoder]) {
                [self decode:frame withSize:frameSize];
            }
        }
            break;
    }
}

- (BOOL)initH264Decoder {
    if (_decoderSession) {
        return YES;
    }
    
    const uint8_t * const parameterSetPointers[2] = {_sps,_pps};
    const size_t parameterSetSizes[2] = {_spsSize,_ppsSize};
    // 根据sps pps 创建解码视频参数
    OSStatus status = CMVideoFormatDescriptionCreateFromH264ParameterSets(kCFAllocatorDefault,
                                                                          2,
                                                                          parameterSetPointers,
                                                                          parameterSetSizes,
                                                                          4,
                                                                          &_decoderFormatDescription);
    if (status != noErr) {
         NSLog(@"H264Decoder::CMVideoFormatDescriptionCreateFromH264ParameterSets failed status = %d", (int)status);
        return NO;
    }
    // 从sps pps 中获取解码视频的宽高信息
    CMVideoDimensions dimensions = CMVideoFormatDescriptionGetDimensions(_decoderFormatDescription);
    
    // kCVPixelBufferPixelFormatTypeKey 解码图像的采样格式
    // kCVPixelBufferWidthKey、kCVPixelBufferHeightKey 解码图像的宽高
    // kCVPixelBufferOpenGLCompatibilityKey制定支持OpenGL渲染，经测试有没有这个参数好像没什么差别
    NSDictionary *destinationPixelBufferAttributes = @{
        (id)kCVPixelBufferPixelFormatTypeKey:@(kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange),
        (id)kCVPixelBufferWidthKey:@(dimensions.width),
        (id)kCVPixelBufferHeightKey:@(dimensions.height),
        (id)kCVPixelBufferOpenGLCompatibilityKey:@(YES),
    };
    
    // 设置解码输出数据回掉
    VTDecompressionOutputCallbackRecord callBackRecord;
    callBackRecord.decompressionOutputCallback = decodeOutputDataCallback;
    callBackRecord.decompressionOutputRefCon = (__bridge void*)self;
    
    //创建解码器
    status = VTDecompressionSessionCreate(kCFAllocatorDefault,
                                          _decoderFormatDescription,
                                          NULL,
                                          (__bridge CFDictionaryRef)destinationPixelBufferAttributes,
                                          &callBackRecord,
                                          &_decoderSession);
    //解码线程数量
    VTSessionSetProperty(_decoderSession,
                         kVTDecompressionPropertyKey_ThreadCount,
                         (__bridge CFTypeRef) @(1));
    //是否时实解码
    VTSessionSetProperty(_decoderSession,
                         kVTDecompressionPropertyKey_RealTime,
                         kCFBooleanTrue);
    
    return YES;
}

void decodeOutputDataCallback(
                                   void * CM_NULLABLE decompressionOutputRefCon,
                                   void * CM_NULLABLE sourceFrameRefCon,
                                   OSStatus status,
                                   VTDecodeInfoFlags infoFlags,
                                   CM_NULLABLE CVImageBufferRef imageBuffer,
                                   CMTime presentationTimeStamp,
                                   CMTime presentationDuration ) {
    CVPixelBufferRetain(imageBuffer);
    FFH264HWDecoder *decoder = (__bridge FFH264HWDecoder *)decompressionOutputRefCon;
    if ([decoder.delegate respondsToSelector:@selector(videoDecoderOutputDataCallback:)]) {
        [decoder.delegate videoDecoderOutputDataCallback:imageBuffer];
    }
}

@end
