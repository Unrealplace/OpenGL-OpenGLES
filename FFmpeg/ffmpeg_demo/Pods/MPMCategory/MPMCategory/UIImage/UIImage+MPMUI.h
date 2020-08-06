//
//  UIImage+MPMUI.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (MPMUI)

/**
 将view转换为image
 
 @param view 视图
 @return UIImage对象
 */
+ (UIImage *)convertViewToImage:(UIView *)view;

/**
 *  通过色值创建图片
 */
+ (UIImage *)imageWithColor:(UIColor *)color;

/**
 通过色值创建图片
 
 @param color 颜色
 @param size 尺寸
 @return 图片对象
 */
+ (UIImage *)imageWithColor:(UIColor *)color size:(CGSize)size;

/**
 生成带有边框的图片
 
 @param size 大小
 @param borderColor 边框颜色
 @param borderWidth 边框宽度
 @param dotLine 是否显示虚线
 @return 图片
 */
+ (UIImage *)imageWithSize:(CGSize)size
               borderColor:(UIColor *)borderColor
               borderWidth:(CGFloat)borderWidth
                 isDotLine:(BOOL)dotLine;

/**
 生成高斯模糊图片
 
 @param image 原始图片
 @return 高斯模糊图片
 */
+ (UIImage *)getGaussianBlurImageWithImage:(UIImage *)image;

/**
 调整图片大小
 
 @param image 需要调整的图片
 @param size 图片大小
 @return 调整后的图片
 */
+ (UIImage *)resizeImage:(UIImage *)image size:(CGSize)size;

/**
 把图片压缩到800以内
 
 @param image 需要调整的图片
 @return 调整后的图片
 */
+ (UIImage *)resizeImage:(UIImage *)image;

/**
 image旋转到正常
 
 @param image 待旋转的图片
 @return 正常图片
 */
+ (UIImage *)imageFixOrientation:(UIImage *)image;

/**
 *  压图片质量
 *
 *  @param originImage image
 *
 *  @return data
 */
+ (NSData *)compressImageQualityWithImage:(UIImage *)originImage toByte:(NSInteger)maxBytes;

/**
 *  压图片大小
 *
 *  @param originImage image
 *  @param maxLength newWidth
 *
 *  @return image
 */
+ (UIImage *)compressImageSizeWithImage:(UIImage *)originImage maxLength:(CGFloat)maxLength;

/**
 *  压图片大小和质量
 *
 *  @param originImage 图片源
 *  @param maxLength 最大宽高限制
 *  @param maxBytes 最大质量限制
 *
 *  @return data
 */
+ (NSData *)compressImageSizeAndQualityWithImage:(UIImage *)originImage maxLength:(NSInteger)maxLength maxBytes:(NSInteger)maxBytes;

/**
 *  图片数组转换成Gif
 *
 *  @param images 合成gif的图片数组
 *  @param delays 每一帧的延时（float类型）
 *  @param loopCount 循环次数 (0 表示无限循环)
 *  @param savePath gif生成的地址
 *
 *  @return BOOL gif生成是否成功
 */
+ (BOOL)convertImagesToGifWithImages:(NSArray *)images delays:(NSArray *)delays loopCount:(NSUInteger)loopCount savePath:(NSString *)savePath;

/**
 根据URL获取首帧图
 
 @param videoURL 视频地址
 @param time 时间戳
 @return 图片
 */
+ (UIImage *)thumbnailImageForVideo:(NSURL *)videoURL atTime:(NSTimeInterval)time;

@end

NS_ASSUME_NONNULL_END
