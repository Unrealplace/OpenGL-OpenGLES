//
//  FFH264HWDecoder.h
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>

NS_ASSUME_NONNULL_BEGIN

@protocol FFHWH264DecoderDelegate <NSObject>

/// h264 硬解码回掉
- (void)videoDecoderOutputDataCallback:(CVImageBufferRef)imageBuffer;

@end

@interface FFH264HWDecoder : NSObject

@property (nonatomic, weak) id <FFHWH264DecoderDelegate> delegate;

/// 解码nalu 数据
- (void)decodeNaluData:(NSData *)naluData;

@end

NS_ASSUME_NONNULL_END
