//
//  UIView+MPMAdd.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Masonry.h"

NS_ASSUME_NONNULL_BEGIN

@interface UIView (MPMAdd)

+ (UIView *)cm_viewWithSuperView:(UIView *)superView
                      constraint:(void(^)(MASConstraintMaker *make))constraint
                configureHandler:(void(^)(UIView *view))configureHandler;

@end

NS_ASSUME_NONNULL_END
