//
//  UIButton+MPMTitleStyle.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/28.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIButton+MPMTitleStyle.h"

#import "UIView+MPMFrame.h"

#import "UILabel+MPMUtils.h"

static CGFloat kDefault_margin = 6.f;

@implementation UIButton (MPMTitleStyle)

- (void)verticalCenterImageAndTitle:(CGFloat)spacing {
    self.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
    self.contentVerticalAlignment = UIControlContentVerticalAlignmentTop;
    
    CGFloat imageViewTop = (self.height - self.imageView.height - self.titleLabel.height - spacing) / 2;
    CGFloat imageViewLeft = (self.width - self.imageView.width) / 2;
    CGFloat titleWidth = [UILabel getWidthWithTitle:self.titleLabel.text font:self.titleLabel.font];
    titleWidth = titleWidth > self.width ? self.width : titleWidth;
    CGFloat titleLabTop = (imageViewTop + self.imageView.height) + spacing;
    CGFloat titleLabLeft = (self.width - titleWidth) / 2 - self.imageView.width;
    self.imageEdgeInsets = UIEdgeInsetsMake(imageViewTop, imageViewLeft, 0, 0);
    self.titleEdgeInsets = UIEdgeInsetsMake(titleLabTop, titleLabLeft, 0, 0);

}

- (void)verticalCenterImageAndTitle {
    [self verticalCenterImageAndTitle:kDefault_margin];
}

#pragma mark - 上下居中，文字在上，图片在下

- (void)verticalCenterTitleAndImage:(CGFloat)spacing {
    self.titleEdgeInsets = UIEdgeInsetsMake(- (self.imageView.height + spacing), - self.imageView.width, 0.0, 0.0);
    CGSize titleSize = self.titleLabel.size;
    self.imageEdgeInsets = UIEdgeInsetsMake(0.0, 0.0, - (self.titleLabel.height + spacing), -titleSize.width);
}

- (void)verticalCenterTitleAndImage {
    [self verticalCenterTitleAndImage:kDefault_margin];
}

#pragma mark - 左右居中，图片在左，文字在右

- (void)horizontalCenterImageAndTitle:(CGFloat)spacing {
    self.titleEdgeInsets = UIEdgeInsetsMake(0.0,  0.0, 0.0,  - spacing);
    self.imageEdgeInsets = UIEdgeInsetsMake(0.0, - spacing, 0.0, 0.0);
}

- (void)horizontalCenterImageAndTitle {
    [self horizontalCenterImageAndTitle:kDefault_margin];
}

#pragma mark - 左右居中，文字在左，图片在右

- (void)horizontalCenterTitleAndImage:(CGFloat)spacing {
    self.titleEdgeInsets = UIEdgeInsetsMake(0.0, - self.imageView.width, 0.0, self.imageView.width + spacing);
    CGSize titleSize = self.titleLabel.size;
    self.imageEdgeInsets = UIEdgeInsetsMake(0.0, titleSize.width + spacing, 0.0, - titleSize.width);
}

- (void)horizontalCenterTitleAndImage {
    [self horizontalCenterTitleAndImage:kDefault_margin];
}

#pragma mark - 文字居中，图片在左边

- (void)horizontalCenterTitleAndImageLeft:(CGFloat)spacing {
    self.imageEdgeInsets = UIEdgeInsetsMake(0.0, - spacing, 0.0, 0.0);
}

- (void)horizontalCenterTitleAndImageLeft {
    [self horizontalCenterTitleAndImageLeft:kDefault_margin];
}

#pragma mark - 文字居中，图片在右边

- (void)horizontalCenterTitleAndImageRight:(CGFloat)spacing {
    self.titleEdgeInsets = UIEdgeInsetsMake(0.0, - self.imageView.width, 0.0, 0.0);
    
    CGSize titleSize = self.titleLabel.size;
    
    self.imageEdgeInsets = UIEdgeInsetsMake(0.0, self.titleLabel.width + self.imageView.width + spacing, 0.0, - titleSize.width);
}

- (void)horizontalCenterTitleAndImageRight {
    [self horizontalCenterTitleAndImageRight:kDefault_margin];
}

@end
