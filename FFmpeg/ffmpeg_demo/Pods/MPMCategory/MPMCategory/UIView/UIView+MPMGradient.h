//
//  UIView+MPMGradient.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, UIColorOrientation) {
    UIColorOrientationHorizontal = 0, //水平方向
    UIColorOrientationVertical = 1,  //垂直方向
};

NS_ASSUME_NONNULL_BEGIN

@interface UIView (MPMGradient)

@property(nullable, copy) NSArray *colors;

@property(nullable, copy) NSArray<NSNumber *> *locations;

@property CGPoint startPoint;
@property CGPoint endPoint;

+ (UIView *_Nullable)gradientViewWithColors:(NSArray<UIColor *> *_Nullable)colors locations:(NSArray<NSNumber *> *_Nullable)locations startPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint;

- (void)setGradientBackgroundWithColors:(NSArray<UIColor *> *_Nullable)colors locations:(NSArray<NSNumber *> *_Nullable)locations startPoint:(CGPoint)startPoint endPoint:(CGPoint)endPoint;

/**
 设置渐变色
 
 @param view 视图
 @param fromColor 开始颜色
 @param toColor 结束颜色
 @param orientation 渐变方向
 @return layer
 */
+ (CAGradientLayer *)setGradualChangingColorWithView:(UIView *)view fromColor:(UIColor *)fromColor toColor:(UIColor *)toColor orientation:(UIColorOrientation)orientation;

@end

NS_ASSUME_NONNULL_END
