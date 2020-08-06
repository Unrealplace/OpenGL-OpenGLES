//
//  UIView+MPMRadius.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "UIImage+MPMRadius.h"

typedef void (^JMRoundedCornerCompletionBlock)(UIImage *image);

NS_ASSUME_NONNULL_BEGIN

@interface UIView (MPMRadius)

/**
 view切半圆角
 
 @param corner UIRectCorner 可填多个 用 | 隔开
 @param size 圆角大小
 */
- (void)maskToCornerRoundingCorners:(UIRectCorner)corner cornerRedius:(CGSize)size;

/**设置圆角背景图，默认 UIViewContentModeScaleAspectFill 模式*/
- (void)jm_setImageWithCornerRadius:(CGFloat)radius
                              image:(UIImage *)image;

/**设置圆角背景图，默认 UIViewContentModeScaleAspectFill 模式*/
- (void)jm_setImageWithJMRadius:(JMRadius)radius
                          image:(UIImage *)image;

/**设置 contentMode 模式的圆角背景图*/
- (void)jm_setImageWithCornerRadius:(CGFloat)radius
                              image:(UIImage *)image
                        contentMode:(UIViewContentMode)contentMode;

/**设置 contentMode 模式的圆角背景图*/
- (void)jm_setImageWithJMRadius:(JMRadius)radius
                          image:(UIImage *)image
                    contentMode:(UIViewContentMode)contentMode;

/**设置圆角边框*/
- (void)jm_setImageWithCornerRadius:(CGFloat)radius
                        borderColor:(UIColor *)borderColor
                        borderWidth:(CGFloat)borderWidth
                    backgroundColor:(UIColor *)backgroundColor;

/**设置圆角边框*/
- (void)jm_setImageWithJMRadius:(JMRadius)radius
                    borderColor:(UIColor *)borderColor
                    borderWidth:(CGFloat)borderWidth
                backgroundColor:(UIColor *)backgroundColor;

/**配置所有属性配置圆角背景图*/
- (void)jm_setImageWithJMRadius:(JMRadius)radius
                          image:(UIImage *)image
                    borderColor:(UIColor *)borderColor
                    borderWidth:(CGFloat)borderWidth
                backgroundColor:(UIColor *)backgroundColor
                    contentMode:(UIViewContentMode)contentMode;

/**配置所有属性配置圆角背景图*/
- (void)jm_setImageWithJMRadius:(JMRadius)radius
                          image:(UIImage *)image
                    borderColor:(UIColor *)borderColor
                    borderWidth:(CGFloat)borderWidth
                backgroundColor:(UIColor *)backgroundColor
                    contentMode:(UIViewContentMode)contentMode
                           size:(CGSize)size
                       forState:(UIControlState)state
                     completion:(JMRoundedCornerCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
