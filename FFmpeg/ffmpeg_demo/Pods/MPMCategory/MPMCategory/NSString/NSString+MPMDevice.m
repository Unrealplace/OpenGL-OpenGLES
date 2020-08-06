//
//  NSString+MPMDevice.m
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSString+MPMDevice.h"

#import <UIKit/UIKit.h>
#import "sys/utsname.h"

@implementation NSString (MPMDevice)

// 设备版本
+ (NSString *)deviceVersion {
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    
    // iPhone
    if ([deviceString isEqualToString:@"iPhone4,1"])    return @"iPhone 4S";
    if ([deviceString isEqualToString:@"iPhone5,1"])    return @"iPhone 5";
    if ([deviceString isEqualToString:@"iPhone5,2"])    return @"iPhone 5";
    if ([deviceString isEqualToString:@"iPhone5,3"])    return @"iPhone 5C";
    if ([deviceString isEqualToString:@"iPhone5,4"])    return @"iPhone 5C";
    if ([deviceString isEqualToString:@"iPhone6,1"])    return @"iPhone 5S";
    if ([deviceString isEqualToString:@"iPhone6,2"])    return @"iPhone 5S";
    if ([deviceString isEqualToString:@"iPhone7,1"])    return @"iPhone 6 Plus";
    if ([deviceString isEqualToString:@"iPhone7,2"])    return @"iPhone 6";
    if ([deviceString isEqualToString:@"iPhone8,1"])    return @"iPhone 6s";
    if ([deviceString isEqualToString:@"iPhone8,2"])    return @"iPhone 6s Plus";
    if ([deviceString isEqualToString:@"iPhone8,4"])    return @"iPhone SE";
    if ([deviceString isEqualToString:@"iPhone9,1"])    return @"iPhone 7";
    if ([deviceString isEqualToString:@"iPhone9,2"])    return @"iPhone 7 Plus";
    if ([deviceString isEqualToString:@"iPhone9,2"])    return @"iPhone 7 Plus";
    if ([deviceString isEqualToString:@"iPhone10,1"])   return @"iPhone 8";
    if ([deviceString isEqualToString:@"iPhone10,2"])   return @"iPhone 8 Plus";
    if ([deviceString isEqualToString:@"iPhone10,3"] ||
        [deviceString isEqualToString:@"iPhone10,6"]) return @"iPhone X";
    if ([deviceString isEqualToString:@"iPhone11,8"]) return @"iPhone XR";
    if ([deviceString isEqualToString:@"iPhone11,2"]) return @"iPhone XS";
    if ([deviceString isEqualToString:@"iPhone11,4"] ||
        [deviceString isEqualToString:@"iPhone11,6"]) return @"iPhone XS Max";
    if ([deviceString isEqualToString:@"iPhone12,1"]) return @"iPhone 11";
    if ([deviceString isEqualToString:@"iPhone12,3"]) return @"iPhone 11 Pro";
    if ([deviceString isEqualToString:@"iPhone12,5"]) return @"iPhone 11 Pro Max";
    
    if ([deviceString isEqualToString:@"i386"])         return @"Simulator";
    if ([deviceString isEqualToString:@"x86_64"])       return @"Simulator";
    
    return deviceString;
}

// 获取app的版本号
+ (NSString *)getAppVersion {
    return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
}

// 获取UUID
+ (NSString *)getUUID {
    return  [[[UIDevice currentDevice]identifierForVendor] UUIDString];
}


// 获取手机系统版本
+ (NSString *)systemVersion {
    
    return [[UIDevice currentDevice] systemVersion];
}

@end
