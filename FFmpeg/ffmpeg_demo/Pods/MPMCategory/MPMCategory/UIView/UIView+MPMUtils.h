//
//  UIView+MPMUtils.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (MPMUtils)

/**
 截屏
 
 @param view 要截的view
 @param block 成功回调
 */
+ (void)cutScreenWithView:(nullable UIView *)view successBlock:(nullable void(^)(UIImage * _Nullable image,NSData * _Nullable imagedata))block;

@end

NS_ASSUME_NONNULL_END
