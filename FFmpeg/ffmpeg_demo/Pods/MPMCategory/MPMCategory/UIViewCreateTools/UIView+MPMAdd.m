//
//  UIView+MPMAdd.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIView+MPMAdd.h"

@implementation UIView (MPMAdd)

+ (UIView *)cm_viewWithSuperView:(UIView *)superView constraint:(void (^)(MASConstraintMaker *))constraint configureHandler:(void (^)(UIView *))configureHandler {
    UIView *view = [UIView new];
    [superView addSubview:view];
    [view mas_makeConstraints:constraint];
    if (configureHandler) {
        configureHandler(view);
    }
    return view;
}

@end
