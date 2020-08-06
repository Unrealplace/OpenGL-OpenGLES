//
//  NSString+MPMCalculate.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    CMCalculateTypeAddition,        // 加法
    CMCalculateTypeSubtraction,     // 减法
    CMCalculateTypeMultiplication,  // 乘法
    CMCalculateTypeDivision,        // 除法
} CMCalculateType;


NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMCalculate)

/**
 计算
 
 @param type 计算类型
 @param baseNumberString 第一个数字字符串
 @param targetNumberString 第二个数字字符串
 */
+ (NSString *)decimalNumberCalculateType:(CMCalculateType)type baseNumber:(NSString *)baseNumberString targetNumber:(NSString *)targetNumberString;

/**
 金额显示 以服务端为准
 
 @param price 服务端返回
 */
+ (NSString *)stringNotRounding:(NSString *)price;

/**
 精度处理
 
 @param sourceString 源字符串
 @param roundingMode 精度模式
 @param scale 保留位数
 */
+ (NSString *)roundBankerWithSourceString:(NSString *)sourceString roundingMode:(NSRoundingMode)roundingMode scale:(NSInteger)scale;

@end

NS_ASSUME_NONNULL_END
