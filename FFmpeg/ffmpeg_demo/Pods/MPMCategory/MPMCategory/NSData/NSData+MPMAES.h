//
//  NSData+MPMAES.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSData (MPMAES)

/**
 AES256加密
 
 @param key 加密字符串
 @return 加密数据
 */
- (NSData *)aes256_encrypt:(NSString *)key;

/**
 AES256解密
 
 @param key 解密字符串
 @return 解密数据
 */
- (NSData *)aes256_decrypt:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
