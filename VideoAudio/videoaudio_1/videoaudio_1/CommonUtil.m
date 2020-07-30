//
//  CommonUtil.m
//  videoaudio_1
//
//  Created by mpm on 2020/7/30.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "CommonUtil.h"

@implementation CommonUtil

+(NSString *)bundlePath:(NSString *)fileName {
    return [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:fileName];
}

+(NSString *)documentsPath:(NSString *)fileName {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:fileName];
}

@end
