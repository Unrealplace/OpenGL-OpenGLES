//
//  NSString+MPMDevice.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMDevice)

// 获取iPhone型号
+ (NSString *)deviceVersion;

// 获取app的版本号
+ (NSString *)getAppVersion;

// 获取UUID
+ (NSString *)getUUID;

// 获取手机系统版本
+ (NSString *)systemVersion;

@end

NS_ASSUME_NONNULL_END
