//
//  UIButton+MPMUtils.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIButton (MPMUtils)

// 重复点击的间隔
@property (nonatomic, assign) NSTimeInterval cs_acceptEventInterval;

@property (nonatomic, assign) NSTimeInterval cs_acceptEventTime;

// 扩大点击区域
- (void)z_enlarge;
- (void)z_setEnlarge:(CGFloat)value;
- (void)z_setEnlargeWithTop:(CGFloat)top right:(CGFloat)right bottom:(CGFloat)bottom left:(CGFloat)left;

@end

NS_ASSUME_NONNULL_END
