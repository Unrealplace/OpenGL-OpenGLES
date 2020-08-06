//
//  UILabel+MPMUtils.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "UILabel+MPMUtils.h"

@implementation UILabel (MPMUtils)

+ (CGFloat)getHeightByWidth:(CGFloat)width title:(NSString *)title font:(UIFont *)font {
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, width, 0)];
    label.text = title;
    label.font = font;
    label.numberOfLines = 0;
    [label sizeToFit];
    CGFloat height = label.frame.size.height;
    return height;
}

+ (CGFloat)getWidthWithTitle:(NSString *)title font:(UIFont *)font {
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 10000, 0)];
    label.text = title;
    label.font = font;
    [label sizeToFit];
    CGFloat width = label.frame.size.width;
    return width;
}

/**
 *  计算字符串高度 （多行）
 *
 *  @param width 字符串的宽度
 *  @param font  字体大小
 *
 *  @return 字符串的尺寸
 */
- (CGSize)heightWithWidth:(CGFloat)width andFont:(UIFont *)font {
    NSDictionary *attribute = @{NSFontAttributeName: font};
    CGSize  size = [self.text boundingRectWithSize:CGSizeMake(width, MAXFLOAT) options:NSStringDrawingUsesFontLeading attributes:attribute context:nil].size;
    return size;
}

/**
 *  计算字符串宽度
 *
 *  @param height 字符串的高度
 *  @param font  字体大小
 *
 *  @return 字符串的尺寸
 */
- (CGSize)widthWithHeight:(CGFloat)height andFont:(UIFont *)font {
    NSDictionary *attribute = @{NSFontAttributeName: font};
    CGSize  size = [self.text boundingRectWithSize:CGSizeMake(MAXFLOAT, height)  options:NSStringDrawingUsesFontLeading attributes:attribute context:nil].size;
    return size;
}

@end
