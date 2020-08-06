//
//  NSString+MPMAES.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMAES)

/**
 AES256加密数据
 
 @param key 加密字符串
 @return 加密结果
 */
- (NSString *)aes256_encrypt:(NSString *)key;

/**
 AES256解密数据
 
 @param key 解密字符串
 @return 解密结果
 */
- (NSString *)aes256_decrypt:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
