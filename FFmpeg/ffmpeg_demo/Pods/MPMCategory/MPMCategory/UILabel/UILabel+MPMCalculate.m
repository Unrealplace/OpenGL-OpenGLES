//
//  UILabel+MPMCalculate.m
//  MPMCategory
//
//  Created by Done.L on 2019/6/28.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UILabel+MPMCalculate.h"

#import "UIView+MPMFrame.h"

@implementation UILabel (MPMCalculate)

- (CGFloat)dynamicWidth {
    CGRect textRect = [self autoRectWithText:self.text Size:CGSizeMake(2000, self.height)];
    CGSize labelsize = textRect.size;
    
    return ceil(labelsize.width);
}

- (CGFloat)dynamicHeight {
    CGRect textRect = [self autoRectWithText:self.text Size:CGSizeMake(self.width, 2000)];
    CGSize labelsize = textRect.size;
    
    return ceil(labelsize.height);
}

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

- (CGFloat)getSpaceLabelHeight:(NSMutableAttributedString *)str width:(CGFloat)width {
    CGSize size = [str boundingRectWithSize:CGSizeMake(width, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin context:nil].size;
    
    return size.height;
}

+ (void)changeLineSpaceForLabel:(UILabel *)label space:(float)space {
    NSString *labelText = label.text;
    NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] initWithString:labelText];
    NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
    [paragraphStyle setLineSpacing:space];
    [attributedString addAttribute:NSParagraphStyleAttributeName value:paragraphStyle range:NSMakeRange(0, [labelText length])];
    label.attributedText = attributedString;
    [label sizeToFit];
}

- (CGRect)autoRectWithText:(NSString *)text Size:(CGSize)size {
    CGRect textRect = [text boundingRectWithSize:size options:NSStringDrawingUsesLineFragmentOrigin attributes:@{NSFontAttributeName:self.font} context:nil];
    
    return textRect;
}

@end
