//
//  UIImage+MPMRadius.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

struct JMRadius {
    CGFloat topLeftRadius;
    CGFloat topRightRadius;
    CGFloat bottomLeftRadius;
    CGFloat bottomRightRadius;
};
typedef struct JMRadius JMRadius;

static inline JMRadius JMRadiusMake(CGFloat topLeftRadius, CGFloat topRightRadius, CGFloat bottomLeftRadius, CGFloat bottomRightRadius) {
    JMRadius radius;
    radius.topLeftRadius = topLeftRadius;
    radius.topRightRadius = topRightRadius;
    radius.bottomLeftRadius = bottomLeftRadius;
    radius.bottomRightRadius = bottomRightRadius;
    return radius;
}

static inline NSString * NSStringFromJMRadius(JMRadius radius) {
    return [NSString stringWithFormat:@"{%.2f, %.2f, %.2f, %.2f}", radius.topLeftRadius, radius.topRightRadius, radius.bottomLeftRadius, radius.bottomRightRadius];
}

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (MPMRadius)

- (UIImage *)jm_setRadius:(CGFloat)radius
                     size:(CGSize)size;

- (UIImage *)jm_setRadius:(CGFloat)radius
                     size:(CGSize)size
              contentMode:(UIViewContentMode)contentMode;

+ (UIImage *)jm_setRadius:(CGFloat)radius
                     size:(CGSize)size
              borderColor:(UIColor *)borderColor
              borderWidth:(CGFloat)borderWidth
          backgroundColor:(UIColor *)backgroundColor;

+ (UIImage *)jm_setJMRadius:(JMRadius)radius
                      image:(UIImage *)image
                       size:(CGSize)size
                borderColor:(UIColor *)borderColor
                borderWidth:(CGFloat)borderWidth
            backgroundColor:(UIColor *)backgroundColor
            withContentMode:(UIViewContentMode)contentMode;


@end

NS_ASSUME_NONNULL_END
