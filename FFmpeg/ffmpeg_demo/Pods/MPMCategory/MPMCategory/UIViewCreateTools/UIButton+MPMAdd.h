//
//  UIButton+MPMAdd.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Masonry.h"

typedef void (^CMVoidBlock)(void);

NS_ASSUME_NONNULL_BEGIN

@interface UIButton (MPMAdd)

+ (UIButton *)cm_buttonWithTitle:(NSString *)title
                      titleColor:(UIColor *)titleColor
                            font:(UIFont *)font
                       superView:(UIView *)superView
                      constraint:(void(^)(MASConstraintMaker *make))constraint
          configureButtonHandler:(void (^)(UIButton *button))configureButtonHandler;

+ (UIButton *)cm_buttonWithSuperView:(UIView *)superView
                          constraint:(void(^)(MASConstraintMaker *make))constraint
              configureButtonHandler:(void (^)(UIButton *button))configureButtonHandler;

+ (UIButton *)cm_buttonWithSuperView:(UIView *)superView
                          constraint:(void(^)(MASConstraintMaker *make))constraint
                       actionHandler:(CMVoidBlock)actionHandler
              configureButtonHandler:(void (^)(UIButton *button))configureButtonHandler;

@end

NS_ASSUME_NONNULL_END
