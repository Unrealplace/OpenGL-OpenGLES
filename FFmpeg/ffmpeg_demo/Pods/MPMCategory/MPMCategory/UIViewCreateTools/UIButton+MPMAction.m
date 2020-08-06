//
//  UIButton+MPMAction.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UIButton+MPMAction.h"

#import <objc/runtime.h>

@implementation UIButton (MPMAction)

- (void)setBlock:(void (^)(void))block {
    objc_setAssociatedObject(self, @selector(block), block, OBJC_ASSOCIATION_COPY_NONATOMIC);
    [self addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
}

- (void(^)(void))block {
    return objc_getAssociatedObject(self, @selector(block));
}

- (void)addEventBlock:(void(^)(void))block {
    self.block = block;
    [self addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)click:(UIButton*)btn {
    if (self.block) {
        self.block();
    }
}

@end
