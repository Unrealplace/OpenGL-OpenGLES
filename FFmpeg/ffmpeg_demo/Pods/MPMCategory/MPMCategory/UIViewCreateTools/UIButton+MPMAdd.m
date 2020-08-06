//
//  UIButton+MPMAdd.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIButton+MPMAdd.h"

#import "UIButton+MPMAction.h"

@implementation UIButton (MPMAdd)

+ (UIButton *)cm_buttonWithTitle:(NSString *)title titleColor:(UIColor *)titleColor font:(UIFont *)font superView:(UIView *)superView constraint:(void (^)(MASConstraintMaker *))constraint configureButtonHandler:(void (^)(UIButton *))configureButtonHandler {
    UIButton *button = [UIButton new];
    [button setTitle:title forState:0];
    [button setTitleColor:titleColor forState:0];
    [button.titleLabel setFont:font];
    [superView addSubview:button];
    [button mas_makeConstraints:constraint];
    
    if (configureButtonHandler) {
        configureButtonHandler(button);
    }
    
    return button;
}

+ (UIButton *)cm_buttonWithSuperView:(UIView *)superView constraint:(void (^)(MASConstraintMaker *))constraint configureButtonHandler:(void (^)(UIButton *))configureButtonHandler {
    UIButton *button = [UIButton new];
    [superView addSubview:button];
    [button mas_makeConstraints:constraint];
    
    if (configureButtonHandler) {
        configureButtonHandler(button);
    }
    
    return button;
}

+ (UIButton *)cm_buttonWithSuperView:(UIView *)superView constraint:(void (^)(MASConstraintMaker *))constraint actionHandler:(CMVoidBlock)actionHandler configureButtonHandler:(void (^)(UIButton *))configureButtonHandler {
    UIButton *button = [UIButton new];
    [superView addSubview:button];
    [button mas_makeConstraints:constraint];
    
    if (configureButtonHandler) {
        configureButtonHandler(button);
    }
    
    if (actionHandler) {
        [button addEventBlock:^{
            actionHandler();
        }];
    }
    
    return button;
}

@end
