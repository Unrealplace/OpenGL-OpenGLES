//
//  UILabel+MPMAdd.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UILabel+MPMAdd.h"

@implementation UILabel (MPMAdd)

+ (UILabel *)cm_labelWithTextColor:(UIColor *)color
                              font:(UIFont *)font
                         superView:(UIView *)superView
                        constraint:(void (^)(MASConstraintMaker *))constraint
                  configureHandler:(void (^)(UILabel *))configureHandler {
    UILabel *label = [UILabel new];
    label.textColor = color;
    label.font = font;
    [superView addSubview:label];
    [label mas_makeConstraints:constraint];
    if (configureHandler) {
        configureHandler(label);
    }
    return label;
}

@end
