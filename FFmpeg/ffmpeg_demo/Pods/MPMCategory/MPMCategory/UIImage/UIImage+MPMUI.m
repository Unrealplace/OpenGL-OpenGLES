//
//  UIImage+MPMUI.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "UIImage+MPMUI.h"

#import <AVFoundation/AVFoundation.h>
#import <Accelerate/Accelerate.h>
#import <AssetsLibrary/ALAssetRepresentation.h>
#import <ImageIO/ImageIO.h>
#import <QuartzCore/QuartzCore.h>
#import <MobileCoreServices/MobileCoreServices.h>

@implementation UIImage (MPMUI)

/**
 将view转换为image
 
 @param view 视图
 @return UIImage对象
 */
+ (UIImage *)convertViewToImage:(UIView *)view {
    // 创建一个bitmap的context
    // 并把它设置成为当前正在使用的context
    UIGraphicsBeginImageContext(view.bounds.size);
    CGContextRef currnetContext = UIGraphicsGetCurrentContext();
    [view.layer renderInContext:currnetContext];
    // 从当前context中创建一个改变大小后的图片
    UIImage* image = UIGraphicsGetImageFromCurrentImageContext();
    // 使当前的context出堆栈
    UIGraphicsEndImageContext();
    return image;
    
}

/**
 *  通过色值创建图片
 */
+ (UIImage *)imageWithColor:(UIColor*)color {
    return [self imageWithColor:color size:CGSizeMake(1, 1)];
}

/**
 通过色值创建图片
 
 @param color 颜色
 @param size 尺寸
 @return 图片对象
 */
+ (UIImage *)imageWithColor:(UIColor *)color size:(CGSize)size {
    CGRect rect = CGRectMake(0,0, size.width, size.height);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}


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
                 isDotLine:(BOOL)dotLine {
    UIGraphicsBeginImageContextWithOptions(size, NO, 0.0);
    [[UIColor clearColor] set];
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextBeginPath(context);
    CGContextSetLineWidth(context, borderWidth);
    CGContextSetStrokeColorWithColor(context, borderColor.CGColor);
    CGFloat lengths[] = { 3, 1 };
    if (dotLine) {
        CGContextSetLineDash(context, 0, lengths, 1);
    }
    CGContextMoveToPoint(context, 0.0, 0.0);
    CGContextAddLineToPoint(context, size.width, 0.0);
    CGContextAddLineToPoint(context, size.width, size.height);
    CGContextAddLineToPoint(context, 0, size.height);
    CGContextAddLineToPoint(context, 0.0, 0.0);
    CGContextStrokePath(context);
    UIImage* image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}


/**
 生成高斯模糊图片
 
 @param image 原始图片
 @return 高斯模糊图片
 */
+ (UIImage *)getGaussianBlurImageWithImage:(UIImage *)image {
    if (image) {
        NSInteger boxSize = (NSInteger)(10 * 2);
        boxSize = boxSize - (boxSize % 2) + 1;
        
        CGImageRef img = image.CGImage;
        
        vImage_Buffer inBuffer, outBuffer, rgbOutBuffer;
        vImage_Error error;
        
        void *pixelBuffer, *convertBuffer;
        
        CGDataProviderRef inProvider = CGImageGetDataProvider(img);
        CFDataRef inBitmapData = CGDataProviderCopyData(inProvider);
        
        convertBuffer = malloc( CGImageGetBytesPerRow(img) * CGImageGetHeight(img) );
        rgbOutBuffer.width = CGImageGetWidth(img);
        rgbOutBuffer.height = CGImageGetHeight(img);
        rgbOutBuffer.rowBytes = CGImageGetBytesPerRow(img);
        rgbOutBuffer.data = convertBuffer;
        
        inBuffer.width = CGImageGetWidth(img);
        inBuffer.height = CGImageGetHeight(img);
        inBuffer.rowBytes = CGImageGetBytesPerRow(img);
        inBuffer.data = (void *)CFDataGetBytePtr(inBitmapData);
        
        pixelBuffer = malloc( CGImageGetBytesPerRow(img) * CGImageGetHeight(img) );
        
        if (pixelBuffer == NULL) {
            NSLog(@"No pixelbuffer");
        }
        
        outBuffer.data = pixelBuffer;
        outBuffer.width = CGImageGetWidth(img);
        outBuffer.height = CGImageGetHeight(img);
        outBuffer.rowBytes = CGImageGetBytesPerRow(img);
        
        void *rgbConvertBuffer = malloc( CGImageGetBytesPerRow(img) * CGImageGetHeight(img) );
        vImage_Buffer outRGBBuffer;
        outRGBBuffer.width = CGImageGetWidth(img);
        outRGBBuffer.height = CGImageGetHeight(img);
        outRGBBuffer.rowBytes = 3;
        outRGBBuffer.data = rgbConvertBuffer;
        
        error = vImageBoxConvolve_ARGB8888(&inBuffer, &outBuffer, NULL, 0, 0, (uint32_t)boxSize, (uint32_t)boxSize, NULL, kvImageEdgeExtend);
        
        if (error) {
            NSLog(@"error from convolution %ld", error);
        }
        const uint8_t mask[] = {2, 1, 0, 3};
        
        vImagePermuteChannels_ARGB8888(&outBuffer, &rgbOutBuffer, mask, kvImageNoFlags);
        
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef ctx = CGBitmapContextCreate(rgbOutBuffer.data,
                                                 rgbOutBuffer.width,
                                                 rgbOutBuffer.height,
                                                 8,
                                                 rgbOutBuffer.rowBytes,
                                                 colorSpace,
                                                 kCGImageAlphaNoneSkipLast);
        CGImageRef imageRef = CGBitmapContextCreateImage(ctx);
        UIImage *returnImage = [UIImage imageWithCGImage:imageRef];
        
        CGContextRelease(ctx);
        
        free(pixelBuffer);
        free(convertBuffer);
        free(rgbConvertBuffer);
        CFRelease(inBitmapData);
        
        CGColorSpaceRelease(colorSpace);
        CGImageRelease(imageRef);
        
        return returnImage;
    }else {
        return nil;
    }
}


/**
 调整图片大小
 
 @param image 需要调整的图片
 @param size 图片大小
 @return 调整后的图片
 */
+ (UIImage *)resizeImage:(UIImage *)image size:(CGSize)size {
    CGFloat width = floor(size.width);
    CGFloat height = floor(size.height);
    UIGraphicsBeginImageContext(CGSizeMake(width, height));
    [image drawInRect:CGRectMake(0, 0, width, height)];
    UIImage *resizeImg = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return resizeImg;
}

+ (UIImage *)resizeImage:(UIImage *)image
{
    float maxLength = 800;
    float currentLength = MAX(image.size.height, image.size.width);
    if (maxLength < currentLength) {
        float scaleRate = maxLength/currentLength;
        image = [UIImage resizeImage:image size:CGSizeMake(image.size.width*scaleRate, image.size.height*scaleRate)];
    }
    return image;
}

/**
 image旋转到正常
 
 @param image 待旋转的图片
 @return 正常图片
 */
+ (UIImage *)imageFixOrientation:(UIImage *)image {
    // No-op if the orientation is already correct
    if(image.imageOrientation == UIImageOrientationUp)
        return image;
    
    // We need to calculate the proper transformation to make the image upright.
    // We do it in 2 steps: Rotate if Left/Right/Down, and then flip if Mirrored.
    CGAffineTransform transform = CGAffineTransformIdentity;
    
    switch(image.imageOrientation) {
        case UIImageOrientationDown:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, image.size.height);
            transform = CGAffineTransformRotate(transform, M_PI);
            break;
            
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width,0);
            transform = CGAffineTransformRotate(transform, M_PI_2);
            break;
            
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform,0, image.size.height);
            transform = CGAffineTransformRotate(transform, -M_PI_2);
            break;
        default:
            break;
    }
    
    switch(image.imageOrientation) {
        case UIImageOrientationUpMirrored:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width,0);
            transform = CGAffineTransformScale(transform, -1,1);
            break;
            
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.height,0);
            transform = CGAffineTransformScale(transform, -1,1);
            break;
        default:
            break;
    }
    
    // Now we draw the underlying CGImage into a new context, applying the transform
    // calculated above.
    CGContextRef ctx = CGBitmapContextCreate(NULL, image.size.width, image.size.height,
                                             CGImageGetBitsPerComponent(image.CGImage),0,
                                             CGImageGetColorSpace(image.CGImage),
                                             CGImageGetBitmapInfo(image.CGImage));
    CGContextConcatCTM(ctx, transform);
    switch(image.imageOrientation) {
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            // Grr...
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.height,image.size.width), image.CGImage);
            break;
            
        default:
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.width,image.size.height), image.CGImage);
            break;
    }
    
    // And now we just create a new UIImage from the drawing context
    CGImageRef cgimg = CGBitmapContextCreateImage(ctx);
    UIImage *img = [UIImage imageWithCGImage:cgimg];
    CGContextRelease(ctx);
    CGImageRelease(cgimg);
    return img;
}

+ (BOOL)convertImagesToGifWithImages:(NSArray *)images delays:(NSArray *)delays loopCount:(NSUInteger)loopCount savePath:(NSString *)savePath {
    // 生成gif是否成功
    BOOL convertSuccess = NO;
    
    CGImageDestinationRef destination = CGImageDestinationCreateWithURL((__bridge CFURLRef)[NSURL fileURLWithPath:savePath], kUTTypeGIF, images.count, NULL);
    if(!loopCount) {
        loopCount = 0;
    }
    
    // loopCount = 0表示无限循环
    NSDictionary *gifProperties = @{(__bridge id)kCGImagePropertyGIFDictionary : @{(__bridge id)kCGImagePropertyGIFLoopCount: @(loopCount)}};
    
    // 默认每一帧间隔0.1秒
    float delay = 0.1;
    for (int i = 0; i < images.count; i++) {
        UIImage *itemImage = images[i];
        if(delays && i < delays.count){
            delay = [delays[i] floatValue];
        }
        
        // 每一帧对应的延迟时间, a float (not double!) in seconds, rounded to centiseconds in the GIF data
        NSDictionary *frameProperties = @{(__bridge id)kCGImagePropertyGIFDictionary : @{(__bridge id)kCGImagePropertyGIFDelayTime: @(delay)}};
        
        CGImageDestinationAddImage(destination, itemImage.CGImage, (__bridge CFDictionaryRef)frameProperties);
    }
    
    CGImageDestinationSetProperties(destination, (__bridge CFDictionaryRef)gifProperties);
    
    if (CGImageDestinationFinalize(destination)) {
        convertSuccess = YES;
    }
    
    CFRelease(destination);
    
    return convertSuccess;
}

+ (NSData *)compressImageQualityWithImage:(UIImage *)image toByte:(NSInteger)maxBytes {
    if (!image) {
        return nil;
    }
    
    CGFloat compression = 1;
    NSData *compressedData = UIImageJPEGRepresentation(image, compression);
    if (compressedData.length < maxBytes) {
        return compressedData;
    }
    
    CGFloat max = 1;
    CGFloat min = 0;
    for (int i = 0; i < 10; ++i) {
        compression = (max + min) / 2;
        // 压缩阈值建议 0.1 - 0.9
        if (compression >= 0.9 || compression <= 0.1) {
            break;
        }
        
        compressedData = UIImageJPEGRepresentation(image, compression);
        if (compressedData.length < maxBytes) {
            min = compression;
        } else if (compressedData.length > maxBytes) {
            max = compression;
        } else {
            break;
        }
    }
    
    return compressedData;
}

/**
 * 压缩比例计算规则：w-->图片宽度，h-->图片高度
 * 1. w / h > 4，        压缩比例(scale) w / 750
 * 2. w / h < 0.25，     压缩比例(scale) h / 750
 * 3. w / h 属于[0.25 4]，压缩比例(scale) w / 1080
 * 4. 对sacle进行调整，为2指数，小数四舍五入，所以scale只有大于等于1.5时才压缩
 */
+ (UIImage *)compressImageSizeWithImage:(UIImage *)originImage maxLength:(CGFloat)maxLength {
    if (!originImage) return nil;
    UIImage *image = originImage;
    CGSize scaleSize = CGSizeMake(originImage.size.width, originImage.size.height);
    CGSize resultSize = [self getCompressSize:scaleSize maxLength:maxLength];
    
    if (!CGSizeEqualToSize(scaleSize, resultSize)) {
        UIGraphicsBeginImageContext(CGSizeMake(resultSize.width, resultSize.height));
        [originImage drawInRect:CGRectMake(0, 0, resultSize.width, resultSize.height)];
        image = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    
    return image;
}

+ (CGSize)getCompressSize:(CGSize)originSize maxLength:(NSInteger)maxLength {
    CGSize result = originSize;
    
    NSInteger width  = originSize.width;
    NSInteger height = originSize.height;
    
    float wTohRatio = ((float) width) / height;
    
    float scale = 0.0;
    if (wTohRatio > 4.0) {
        scale = ((float) width) / 2484;
    } else if (wTohRatio < 0.25) {
        scale = ((float) height) / 2484;
    } else {
        scale = ((float) MAX(width, height)) / maxLength;
    }
    
    if (scale >= 1.5) {
        scale = [self getCompressScale:scale];
        NSInteger width  = originSize.width / scale;
        NSInteger height = originSize.height / scale;
        
        result = CGSizeMake(width, height);
        NSLog(@"输出图片尺寸压缩比为 %f", scale);
    } else {
        NSLog(@"按照原图尺寸输出，质量压缩'可能'达不到要求，请注意修改目标尺寸！！！");
    }
    
    return result;
}

+ (float)getCompressScale:(float)originScale {
    float f = log2f(originScale);               // 计算以以2为底originScale的对数
    float ceilF  = ceilf(f);                    // 向上取整
    float floorF = floorf(f);                   // 向下取整
    
    float ceilScale  = powf(2, ceilF);          // 2的ceilF次幂
    float floorScale = powf(2, floorF);         // 2的floorF次幂
    
    float dDuration1 = ceilScale - originScale;
    float dDuration2 = originScale - floorScale;
    
    return dDuration1 <= dDuration2 ? ceilScale: floorScale; // 取最近的2次幂，小数四舍五入
}

+ (NSData *)compressImageSizeAndQualityWithImage:(UIImage *)originImage maxLength:(NSInteger)maxLength maxBytes:(NSInteger)maxBytes {
    UIImage *image = [self compressImageSizeWithImage:originImage maxLength:maxLength];
    NSData *data = [self compressImageQualityWithImage:image toByte:maxBytes];
    
    return data;
}

+ (UIImage *)thumbnailImageForVideo:(NSURL *)videoURL atTime:(NSTimeInterval)time {
    AVURLAsset *asset = [[AVURLAsset alloc] initWithURL:videoURL options:nil];
    NSParameterAssert(asset);
    AVAssetImageGenerator *assetImageGenerator =[[AVAssetImageGenerator alloc] initWithAsset:asset];
    assetImageGenerator.appliesPreferredTrackTransform = YES;
    assetImageGenerator.apertureMode = AVAssetImageGeneratorApertureModeEncodedPixels;
    
    CGImageRef thumbnailImageRef = NULL;
    CFTimeInterval thumbnailImageTime = time;
    NSError *thumbnailImageGenerationError = nil;
    thumbnailImageRef = [assetImageGenerator copyCGImageAtTime:CMTimeMake(thumbnailImageTime, 60)actualTime:NULL error:&thumbnailImageGenerationError];
    
    UIImage *thumbnailImage = thumbnailImageRef ? [[UIImage alloc] initWithCGImage: thumbnailImageRef] : nil;
    
    return thumbnailImage;
}

@end
