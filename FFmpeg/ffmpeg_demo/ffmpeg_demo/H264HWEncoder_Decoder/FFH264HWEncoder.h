//
//  FFH264HWEncoder.h
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <VideoToolbox/VideoToolbox.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, FFVideoEncoderProfileLevel) {
    FFVideoEncoderProfileLevelBP,
    FFVideoEncoderProfileLevelMP,
    FFVideoEncoderProfileLevelHP
};

@interface FFVideoEncoderParam : NSObject

/// profilelevel 默认BP
@property (nonatomic, assign) FFVideoEncoderProfileLevel profileLevel;

/// 编码宽度
@property (nonatomic, assign) int32_t encodeWidth;

/// 编码高度
@property (nonatomic, assign) int32_t encodeHeight;

/// 编码类型
@property (nonatomic, assign) CMVideoCodecType encodeType;

/// 码率 kbps
@property (nonatomic, assign) NSInteger bitRate;

/// 帧率 fps
@property (nonatomic, assign) NSInteger frameRate;

/// 最大I帧间隔，单位秒
@property (nonatomic, assign) NSInteger maxKeyFrameInterVal;

/// 是否允许B帧
@property (nonatomic, assign) BOOL allowFrameReordering;

@end

@protocol FFVideoEncoderDelegate <NSObject>

- (void)videoEncodeOutputDataCallback:(NSData *)data isKeyFrame:(BOOL)isKeyFrame;

@end

@interface FFH264HWEncoder : NSObject

@property (nonatomic, weak) id<FFVideoEncoderDelegate> delegate;

@property (nonatomic, strong) FFVideoEncoderParam *param;

/// 初始化并配置编码参数
/// @param param 编码参数
- (instancetype)initWithParam:(FFVideoEncoderParam *)param;

/// 输入待编码数据
/// @param sampleBuffer 待编码数据
/// @param forecekeyFrame 是否强制I帧
- (BOOL)videoEncodeInputData:(CMSampleBufferRef)sampleBuffer forceKeyFrame:(BOOL)forecekeyFrame;

/// 编码过程中调整码率
/// @param bitRate 码率
- (BOOL)adjustBitRate:(NSInteger)bitRate;

/// 开始准备编码
- (BOOL)startVideoEncode;

/// 结束编码
- (BOOL)stopVideoEncode;

@end

NS_ASSUME_NONNULL_END
