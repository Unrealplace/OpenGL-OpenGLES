//
//  UILabel+MPMUtils.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UILabel (MPMUtils)

+ (CGFloat)getHeightByWidth:(CGFloat)width title:(NSString *)title font:(UIFont*)font;
+ (CGFloat)getWidthWithTitle:(NSString *)title font:(UIFont *)font;

- (CGSize)heightWithWidth:(CGFloat)width andFont:(UIFont *)font;
- (CGSize)widthWithHeight:(CGFloat)height andFont:(UIFont *)font;

@end

NS_ASSUME_NONNULL_END
