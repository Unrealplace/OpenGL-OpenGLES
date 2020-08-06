//
//  UIAlertAction+MPMUI.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "UIAlertAction+MPMUI.h"

#import <objc/runtime.h>

@implementation UIAlertAction (MPMUI)

- (void)setTextColor:(UIColor *)color {
    if (color) {
        uint count = 0;
        Ivar *ivars = class_copyIvarList(self.class, &count);
        for (int i = 0 ; i < count; i ++) {
            Ivar ivar = ivars[i];
            const char *name = ivar_getName(ivar);
            if ([[NSString stringWithUTF8String:name] isEqualToString:@"_titleTextColor"]) {
                [self setValue:color forKey:@"_titleTextColor"];
            }
        }
    }
}

@end
