//
//  NSString+MPMFont.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMFont)

/**
 计算字符串尺寸
 
 @param width 宽度
 @param font 字体
 */
- (CGRect)autoRectWithWidth:(CGFloat)width font:(UIFont *)font;

/**
 计算字符串尺寸
 
 @param font 字体
 @param maxSize 最大尺寸
 */
- (CGSize)sizeWithFont:(UIFont *)font maxSize:(CGSize)maxSize;

@end

NS_ASSUME_NONNULL_END
