//
//  UIView+MPMAction.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIView+MPMAction.h"

#import <objc/runtime.h>

static const void *CMBlockTapKey = &CMBlockTapKey;

@interface UIView ()

@property void(^clickBlock)(id);

@end

@implementation UIView (MPMAction)

- (void)setClickBlock:(void (^)(id))clickBlock {
    objc_setAssociatedObject(self, CMBlockTapKey, clickBlock, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (void (^)(id))clickBlock {
    return objc_getAssociatedObject(self, CMBlockTapKey);
}

- (void)addTapEvent:(void (^)(id _Nonnull))block {
    self.clickBlock = block;
    if (![self gestureRecognizers]) {
        self.userInteractionEnabled = YES;
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(blockAction)];
        [self addGestureRecognizer:tap];
    }
}

- (void)blockAction {
    if (self.clickBlock) {
        self.clickBlock(self);
    }
}

@end
