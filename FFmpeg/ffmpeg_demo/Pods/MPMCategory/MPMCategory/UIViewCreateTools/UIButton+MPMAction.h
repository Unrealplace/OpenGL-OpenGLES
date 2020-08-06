//
//  UIButton+MPMAction.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIButton (MPMAction)

- (void)addEventBlock:(void(^)(void))block;

@end

NS_ASSUME_NONNULL_END
