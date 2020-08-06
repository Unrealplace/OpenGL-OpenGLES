//
//  UIFont+MPMUtils.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIFont (MPMUtils)

// 思源黑体 - Regular
+ (UIFont *)meipingmi_SourceHanSansCN_Regular:(CGFloat)fontSize;

// 思源黑体 - Normal
+ (UIFont *)meipingmi_SourceHanSansCN_Normal:(CGFloat)fontSize;

// 思源黑体 - Medium
+ (UIFont *)meipingmi_SourceHanSansCN_Medium:(CGFloat)fontSize;

// 思源黑体 - Bold
+ (UIFont *)meipingmi_SourceHanSansCN_Bold:(CGFloat)fontSize;


// 苹方 - Regular
+ (UIFont *)meipingmi_PingFangSC_Regular:(CGFloat)fontSize;

// 苹方 - Medium
+ (UIFont *)meipingmi_PingFangSC_Medium:(CGFloat)fontSize;

// 苹方 - Semibold
+ (UIFont *)meipingmi_PingFangSC_Semibold:(CGFloat)fontSize;

// 苹方 - Light
+ (UIFont *)meipingmi_PingFangSC_Light:(CGFloat)fontSize;

// DINAlternate - Bold
+ (UIFont *)meipingmi_DINAlternate_Bold:(CGFloat)fontSize;

// DINPro-Regular
+ (UIFont *)meipingmi_DINPro_Regular:(CGFloat)fontSize;

// DINPro-Medium
+ (UIFont *)meipingmi_DINPro_Medium:(CGFloat)fontSize;

// DIN-Bold
+ (UIFont *)meipingmi_DIN_Bold:(CGFloat)fontSize;

// Helvetica
+ (UIFont *)meipingmi_Helvetica:(CGFloat)fontSize;

@end

NS_ASSUME_NONNULL_END
