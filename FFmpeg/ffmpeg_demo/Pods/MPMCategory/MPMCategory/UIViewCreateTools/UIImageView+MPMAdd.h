//
//  UIImageView+MPMAdd.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Masonry.h"

NS_ASSUME_NONNULL_BEGIN

@interface UIImageView (MPMAdd)

+ (UIImageView *)cm_imageViewWithIcon:(NSString *)iconName
                            superView:(UIView *)superView
                           constraint:(void(^)(MASConstraintMaker *make))constraint
            configureImageViewHandler:(void (^)(UIImageView *iconView))configureImageViewHandler;

@end

NS_ASSUME_NONNULL_END
