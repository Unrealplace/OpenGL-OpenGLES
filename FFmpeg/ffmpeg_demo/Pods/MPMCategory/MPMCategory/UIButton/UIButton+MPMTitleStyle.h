//
//  UIButton+MPMTitleStyle.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/28.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIButton (MPMTitleStyle)

// 上下居中，图片在上，文字在下
- (void)verticalCenterImageAndTitle:(CGFloat)spacing;
- (void)verticalCenterImageAndTitle;

// 上下居中，文字在上，图片在下
- (void)verticalCenterTitleAndImage:(CGFloat)spacing;
- (void)verticalCenterTitleAndImage;

// 左右居中，文字在左，图片在右
- (void)horizontalCenterTitleAndImage:(CGFloat)spacing;
- (void)horizontalCenterTitleAndImage;

// 左右居中，图片在左，文字在右
- (void)horizontalCenterImageAndTitle:(CGFloat)spacing;
- (void)horizontalCenterImageAndTitle;

// 文字居中，图片在左边
- (void)horizontalCenterTitleAndImageLeft:(CGFloat)spacing;
- (void)horizontalCenterTitleAndImageLeft;

// 文字居中，图片在右边
- (void)horizontalCenterTitleAndImageRight:(CGFloat)spacing;
- (void)horizontalCenterTitleAndImageRight;

@end

NS_ASSUME_NONNULL_END
