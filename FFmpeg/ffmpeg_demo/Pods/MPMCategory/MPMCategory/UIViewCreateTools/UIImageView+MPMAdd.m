//
//  UIImageView+MPMAdd.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIImageView+MPMAdd.h"

@implementation UIImageView (MPMAdd)

+ (UIImageView *)cm_imageViewWithIcon:(NSString *)iconName
                            superView:(UIView *)superView
                           constraint:(void (^)(MASConstraintMaker *))constraint
            configureImageViewHandler:(void (^)(UIImageView *))configureImageViewHandler {
    UIImageView *imageView = [UIImageView new];
    if (iconName) {
        imageView.image = [UIImage imageNamed:iconName];
    }
    
    [superView addSubview:imageView];
    [imageView mas_makeConstraints:constraint];
    
    if (configureImageViewHandler) {
        configureImageViewHandler(imageView);
    }
    
    return imageView;
}

@end
