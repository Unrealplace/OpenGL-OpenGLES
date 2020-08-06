//
//  NSString+MPMURL.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMURL)

#pragma mark - # 编码
/**
 *  url编码，使用 NSUTF8StringEncoding 格式
 *
 *  @return encode后的字符串
 */
- (NSString *)urlEncode;

/**
 *  url编码
 *
 *  @param encoding 编码模式
 *
 *  @return encode后的字符串
 */
- (NSString *)urlEncodeUsingEncoding:(NSStringEncoding)encoding;


#pragma mark - # 解码
/**
 *  url解码，使用 NSUTF8StringEncoding 格式
 *
 *  @return decode后的字符串
 */
- (NSString *)urlDecode;

/**
 *  url解码
 *
 *  @param encoding 编码模式
 *
 *  @return decode后的字符串
 */
- (NSString *)urlDecodeUsingEncoding:(NSStringEncoding)encoding;

/**
 截取URL中的参数
 
 @param url 字符串
 */
+ (NSMutableDictionary *)parseURLParameters:(NSString *)url;

@end

NS_ASSUME_NONNULL_END
