//
//  UILabel+MPMCalculate.h
//  MPMCategory
//
//  Created by Done.L on 2019/6/28.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UILabel (MPMCalculate)

- (CGFloat)dynamicWidth;
- (CGFloat)dynamicHeight;

+ (CGFloat)getHeightByWidth:(CGFloat)width title:(NSString *)title font:(UIFont *)font;

+ (CGFloat)getWidthWithTitle:(NSString *)title font:(UIFont *)font;

- (CGFloat)getSpaceLabelHeight:(NSMutableAttributedString *)str width:(CGFloat)width;

// 改变行间距
+ (void)changeLineSpaceForLabel:(UILabel *)label space:(float)space;

@end

NS_ASSUME_NONNULL_END
