//
//  UIView+MPMUtils.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "UIView+MPMUtils.h"

@implementation UIView (MPMUtils)

+ (void)cutScreenWithView:(nullable UIView *)view successBlock:(nullable void(^)(UIImage * _Nullable image,NSData * _Nullable imagedata))block {
    UIGraphicsBeginImageContextWithOptions(view.bounds.size, NO, 0);
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    [view.layer renderInContext:ctx];
    UIImage * newImage = UIGraphicsGetImageFromCurrentImageContext();
    NSData * data = UIImageJPEGRepresentation(newImage, 1);
    UIGraphicsEndImageContext();
    block(newImage,data);
}

@end
