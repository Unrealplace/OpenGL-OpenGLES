//
//  FFH264HWEncoder.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "FFH264HWEncoder.h"

@implementation FFVideoEncoderParam

- (instancetype)init {
    if (self = [super init]) {
        self.bitRate = 1024 * 1024;
        self.frameRate = 15;
        self.encodeType = kCMVideoCodecType_H264;
        self.profileLevel = FFVideoEncoderProfileLevelBP;
        self.maxKeyFrameInterVal = 240;
        self.allowFrameReordering = NO;
    }
    
    return self;
}

@end

@interface FFH264HWEncoder()

@property (nonatomic, assign) VTCompressionSessionRef compressionSessionRef;

@property (nonatomic, strong) dispatch_queue_t operationQueue;

@end

@implementation FFH264HWEncoder

- (void)dealloc {
    NSLog(@"%s",__func__);
    if (NULL == _compressionSessionRef) {
        return;
    }
    
    VTCompressionSessionCompleteFrames(_compressionSessionRef, kCMTimeInvalid);
    VTCompressionSessionInvalidate(_compressionSessionRef);
    CFRelease(_compressionSessionRef);
    _compressionSessionRef = NULL;
}

- (instancetype)initWithParam:(FFVideoEncoderParam *)param {
    if (self = [super init]) {
        self.param = param;
        
        //        allocator：内存分配器，填NULL为默认分配器
        //        width、height：视频帧像素的宽高，如果编码器不支持这个宽高的话可能会改变
        //        codecType：编码类型，枚举
        //        encoderSpecification：指定特定的编码器，填NULL的话由VideoToolBox自动选择
        //        sourceImageBufferAttributes：源像素缓冲区的属性，如果这个参数有值的话，VideoToolBox会创建一个缓冲池，不需要缓冲池可以设置为NULL
        //        compressedDataAllocator：压缩后数据的内存分配器，填NULL使用默认分配器
        //        outputCallback：视频编码后输出数据回调函数
        //        outputCallbackRefCon：回调函数中的自定义指针，我们通常传self，在回调函数中就可以拿到当前类的方法和属性了
        //        compressionSessionOut：编码器句柄，传入编码器的指针
        
        OSStatus status = VTCompressionSessionCreate(NULL,
                                                     param.encodeWidth,
                                                     param.encodeHeight,
                                                     param.encodeType,
                                                     NULL,
                                                     NULL,
                                                     NULL,
                                                     encodeOutputDataCallBack,
                                                     (__bridge void *)(self),
                                                     &_compressionSessionRef);
        
        if (status != noErr) {
            NSLog(@"HWEncoder::VTCompressionSessionCreate:failed status:%d",(int)status);
            return nil;
        }
        
        if (self.compressionSessionRef == NULL) {
            NSLog(@"HWEncoder::调用顺序错误");
            return nil;
        }
        
        // 设置码率 平均码率
        
        if (![self adjustBitRate:self.param.bitRate]) {
            return nil;
        }
        
        // ProfileLevel，h264的协议等级，不同的清晰度使用不同的ProfileLevel。
        CFStringRef profileRef = kVTProfileLevel_H264_High_AutoLevel;
        switch (self.param.profileLevel) {
            case FFVideoEncoderProfileLevelBP:
                profileRef = kVTProfileLevel_H264_Baseline_3_1;
                break;
            case FFVideoEncoderProfileLevelMP:
                profileRef = kVTProfileLevel_H264_Main_3_1;
                break;
            case FFVideoEncoderProfileLevelHP:
                profileRef = kVTProfileLevel_H264_High_3_1;
                break;
                
            default:
                break;
        }
        
        status = VTSessionSetProperty(_compressionSessionRef,
                                      kVTCompressionPropertyKey_ProfileLevel,
                                      profileRef);
        CFRelease(profileRef);
        if (noErr != status) {
            NSLog(@"HWEncoder::kVTCompressionPropertyKey_ProfileLevel failed status:%d", (int)status);
            return nil;
        }
        
        // 设置实时编码输出，避免延时
        status = VTSessionSetProperty(_compressionSessionRef,
                                      kVTCompressionPropertyKey_RealTime,
                                      kCFBooleanTrue);
        if (noErr != status)
        {
            NSLog(@"HWEncoder::kVTCompressionPropertyKey_RealTime failed status:%d", (int)status);
            return nil;
        }
        
        // 配置是否产生B帧
        status = VTSessionSetProperty(_compressionSessionRef,
                                      kVTCompressionPropertyKey_AllowFrameReordering,
                                      self.param.allowFrameReordering ? kCFBooleanTrue : kCFBooleanFalse);
        if (noErr != status)
        {
            NSLog(@"HWEncoder::kVTCompressionPropertyKey_AllowFrameReordering failed status:%d", (int)status);
            return nil;
        }
        
        // 配置I帧间隔
        status = VTSessionSetProperty(_compressionSessionRef,
                                      kVTCompressionPropertyKey_MaxKeyFrameInterval,
                                      (__bridge CFTypeRef)@(self.param.frameRate * self.param.maxKeyFrameInterVal));
        if (noErr != status)
        {
            NSLog(@"HWEncoder::kVTCompressionPropertyKey_MaxKeyFrameInterval failed status:%d", (int)status);
            return nil;
        }
        
        status = VTSessionSetProperty(_compressionSessionRef,
                                      kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration,
                                      (__bridge CFTypeRef)@(self.param.maxKeyFrameInterVal));
        if (noErr != status)
        {
            NSLog(@"VEVideoEncoder::kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration failed status:%d", (int)status);
            return nil;
        }
        
        // 编码器准备编码
        status = VTCompressionSessionPrepareToEncodeFrames(_compressionSessionRef);
        
        if (noErr != status)
        {
            NSLog(@"HWEncoder::VTCompressionSessionPrepareToEncodeFrames failed status:%d", (int)status);
            return nil;
        }
    }
    
    return self;
}

- (BOOL)adjustBitRate:(NSInteger)bitRate {
    if (bitRate <= 0)
    {
        NSLog(@"VEVideoEncoder::adjustBitRate failed! bitRate <= 0");
        return NO;
    }
    OSStatus status = VTSessionSetProperty(_compressionSessionRef, kVTCompressionPropertyKey_AverageBitRate, (__bridge CFTypeRef)@(bitRate));
    if (noErr != status)
    {
        NSLog(@"VEVideoEncoder::kVTCompressionPropertyKey_AverageBitRate failed status:%d", (int)status);
        return NO;
    }
    
    // 参考webRTC 限制最大码率不超过平均码率的1.5倍
    int64_t dataLimitBytesPerSecondValue =
    bitRate * 1.5 / 8;
    CFNumberRef bytesPerSecond = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &dataLimitBytesPerSecondValue);
    int64_t oneSecondValue = 1;
    CFNumberRef oneSecond = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &oneSecondValue);
    const void* nums[2] = {bytesPerSecond, oneSecond};
    CFArrayRef dataRateLimits = CFArrayCreate(NULL, nums, 2, &kCFTypeArrayCallBacks);
    status = VTSessionSetProperty( _compressionSessionRef, kVTCompressionPropertyKey_DataRateLimits, dataRateLimits);
    if (noErr != status)
    {
        NSLog(@"VEVideoEncoder::kVTCompressionPropertyKey_DataRateLimits failed status:%d", (int)status);
        return NO;
    }
    return YES;
}

- (BOOL)videoEncodeInputData:(CMSampleBufferRef)sampleBuffer forceKeyFrame:(BOOL)forecekeyFrame {
    if (_compressionSessionRef == NULL) {
        return NO;
    }
    if (sampleBuffer == nil) {
        return NO;
    }
    
    CVImageBufferRef pixelBuffer = (CVImageBufferRef)CMSampleBufferGetImageBuffer(sampleBuffer);
    NSDictionary *frameProperties = @{(__bridge NSString *)kVTEncodeFrameOptionKey_ForceKeyFrame:@(forecekeyFrame)};
    
    OSStatus status = VTCompressionSessionEncodeFrame(_compressionSessionRef,
                                                      pixelBuffer,
                                                      kCMTimeInvalid,
                                                      kCMTimeInvalid,
                                                      (__bridge CFDictionaryRef)frameProperties,
                                                      NULL,
                                                      NULL);
    if (noErr != status) {
        NSLog(@"HWEncoder::VTCompressionSessionEncodeFrame failed! status:%d", (int)status);
        return NO;
    }
    return YES;
}

- (BOOL)startVideoEncode {
    if (NULL == self.compressionSessionRef)
    {
        NSLog(@"HWEncoder::调用顺序错误");
        return NO;
    }
    
    // 编码器准备编码
    OSStatus status = VTCompressionSessionPrepareToEncodeFrames(_compressionSessionRef);
    if (noErr != status)
    {
        NSLog(@"HWEncoder::VTCompressionSessionPrepareToEncodeFrames failed status:%d", (int)status);
        return NO;
    }
    return YES;
}

- (BOOL)stopVideoEncode {
    if (self.compressionSessionRef == NULL) {
        return NO;
    }
    
    OSStatus status = VTCompressionSessionCompleteFrames(_compressionSessionRef, kCMTimeInvalid);
    if (noErr != status)
    {
        NSLog(@"HWEncoder::VTCompressionSessionCompleteFrames failed! status:%d", (int)status);
        return NO;
    }
    return YES;
}

// 编码成功的回掉函数
void encodeOutputDataCallBack(void * CM_NULLABLE outputCallbackRefCon,
                              void * CM_NULLABLE sourceFrameRefCon,
                              OSStatus status,
                              VTEncodeInfoFlags infoFlags,
                              CM_NULLABLE CMSampleBufferRef sampleBuffer) {
    if (status != noErr || sampleBuffer == nil) {
        NSLog(@"HWEncoder::encodeOutputCallback Error : %d!", (int)status);
        return;
    }
    
    if (outputCallbackRefCon == nil) {
        return;
    }
    
    if (!CMSampleBufferDataIsReady(sampleBuffer)) {
        return;
    }
    
    if (infoFlags & kVTEncodeInfo_FrameDropped) {
        NSLog(@"HWEncoder::H264 encode dropped frame.");
        return;
    }
    
    FFH264HWEncoder *encoder = (__bridge FFH264HWEncoder*)outputCallbackRefCon;
    // \x 表示16进制数
    const char header[] = "\x00\x00\x00\x01";
    size_t headerLen = sizeof(header) - 1;
    NSData *headerData = [NSData dataWithBytes:header length:headerLen];
    bool isKeyFrame = !CFDictionaryContainsKey((CFDictionaryRef) CFArrayGetValueAtIndex(CMSampleBufferGetSampleAttachmentsArray(sampleBuffer, true), 0), (const void *)kCMSampleAttachmentKey_NotSync);
    
    if (isKeyFrame) {
        NSLog(@"HWEncoder::编码了一个关键帧");
        CMFormatDescriptionRef formatedescriptionRef = CMSampleBufferGetFormatDescription(sampleBuffer);
        size_t sParameterSetSize,sParameterSetCount;
        const uint8_t *sParameterSet;
        OSStatus spsStatus = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(formatedescriptionRef,
                                                                                0,
                                                                                &sParameterSet,
                                                                                &sParameterSetSize,
                                                                                &sParameterSetCount,
                                                                                0);
        size_t pParameterSetSize, pParameterSetCount;
        const uint8_t *pParameterSet;
        OSStatus ppsStatus = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(formatedescriptionRef,
                                                                                1,
                                                                                &pParameterSet,
                                                                                &pParameterSetSize,
                                                                                &pParameterSetCount,
                                                                                0);
        if (noErr == spsStatus && noErr == ppsStatus) {
            NSData *sps = [NSData dataWithBytes:sParameterSet length:sParameterSetSize];
            NSData *pps = [NSData dataWithBytes:pParameterSet length:pParameterSetSize];
            NSMutableData *spsData = [NSMutableData data];
            [spsData appendData:headerData];
            [spsData appendData:sps];
            if ([encoder.delegate respondsToSelector:@selector(videoEncodeOutputDataCallback:isKeyFrame:)]) {
                [encoder.delegate videoEncodeOutputDataCallback:spsData isKeyFrame:isKeyFrame];
            }
            
            NSMutableData *ppsData = [NSMutableData data];
            [ppsData appendData:headerData];
            [ppsData appendData:pps];
            if ([encoder.delegate respondsToSelector:@selector(videoEncodeOutputDataCallback:isKeyFrame:)]) {
                [encoder.delegate videoEncodeOutputDataCallback:ppsData isKeyFrame:isKeyFrame];
            }
            
        }
    }
    
    CMBlockBufferRef blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer);
    size_t length,totalLength;
    char *dataPointer;
    status = CMBlockBufferGetDataPointer(blockBuffer,
                                         0,
                                         &length,
                                         &totalLength,
                                         &dataPointer);
    if (noErr != status) {
         NSLog(@"HWEncoder::CMBlockBufferGetDataPointer Error : %d!", (int)status);
         return;
    }
    
    size_t bufferOffset = 0;
    static const int avcHeaderLength = 4;
    while (bufferOffset < totalLength - avcHeaderLength) {
        // 读取 NAL 单元长度
        uint32_t nalUnitLength = 0;
        memcpy(&nalUnitLength, dataPointer + bufferOffset, avcHeaderLength);
        // 大端转小端
        nalUnitLength = CFSwapInt32BigToHost(nalUnitLength);
        NSData *frameData = [[NSData alloc] initWithBytes:(dataPointer + bufferOffset + avcHeaderLength) length:nalUnitLength];
        
        NSMutableData *outputFrameData = [NSMutableData data];
        [outputFrameData appendData:headerData];
        [outputFrameData appendData:frameData];
        
        bufferOffset += avcHeaderLength + nalUnitLength;
        
        if ([encoder.delegate respondsToSelector:@selector(videoEncodeOutputDataCallback:isKeyFrame:)])
        {
            [encoder.delegate videoEncodeOutputDataCallback:outputFrameData isKeyFrame:isKeyFrame];
        }
    }
}



@end
