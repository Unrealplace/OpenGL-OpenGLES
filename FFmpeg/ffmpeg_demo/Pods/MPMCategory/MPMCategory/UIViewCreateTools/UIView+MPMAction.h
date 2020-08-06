//
//  UIView+MPMAction.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (MPMAction)

- (void)addTapEvent:(void(^)(id obj))block;

@end

NS_ASSUME_NONNULL_END
