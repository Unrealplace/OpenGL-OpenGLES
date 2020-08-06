//
//  NSString+MPMCalculate.m
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSString+MPMCalculate.h"

#import "NSString+MPMTypeCheck.h"

@implementation NSString (MPMCalculate)

+ (NSString *)decimalNumberCalculateType:(CMCalculateType)type baseNumber:(NSString *)baseNumberString targetNumber:(NSString *)targetNumberString {
    NSDecimalNumber *baseNumber = [NSDecimalNumber decimalNumberWithString:baseNumberString];
    NSDecimalNumber *targetNumber = [NSDecimalNumber decimalNumberWithString:targetNumberString];
    NSDecimalNumber *product = nil;
    switch (type) {
        case CMCalculateTypeAddition: {
            product = [baseNumber decimalNumberByAdding:targetNumber];
        }
            break;
        case CMCalculateTypeSubtraction: {
            product = [baseNumber decimalNumberBySubtracting:targetNumber];
        }
            break;
        case CMCalculateTypeMultiplication: {
            product = [baseNumber decimalNumberByMultiplyingBy:targetNumber];
        }
            break;
        case CMCalculateTypeDivision: {
            product = [baseNumber decimalNumberByDividingBy:targetNumber];
        }
            break;
        default:
            break;
    }
    return [product stringValue];
}

/**
 金额显示 以服务端为准
 */
+ (NSString *)stringNotRounding:(NSString *)price {
    
    NSDecimalNumberHandler *roundingBehavior = [NSDecimalNumberHandler decimalNumberHandlerWithRoundingMode:NSRoundDown scale:2 raiseOnExactness:NO raiseOnOverflow:NO raiseOnUnderflow:NO raiseOnDivideByZero:NO];
    NSDecimalNumber *ouncesDecimal;
    NSDecimalNumber *roundedOunces;
    // 精度统一取double类型防止丢失, .2f防止服务端出现数据错乱小数点位数很长的异常
    ouncesDecimal = [[NSDecimalNumber alloc] initWithString:[NSString stringWithFormat:@"%.2f", price.doubleValue]];
    roundedOunces = [ouncesDecimal decimalNumberByRoundingAccordingToBehavior:roundingBehavior];
    return [NSString stringWithFormat:@"%@",roundedOunces];
}

/**
 精度处理
 
 @param sourceString 源字符串
 @param roundingMode 精度模式
 @param scale 保留位数
 */
+ (NSString *)roundBankerWithSourceString:(NSString *)sourceString roundingMode:(NSRoundingMode)roundingMode scale:(NSInteger)scale {
    if ([NSString isBlankString:sourceString]) {
        sourceString = @"0";
    }
    
    if ([sourceString containsString:@"万"]) {
        return sourceString;
    }
    NSDecimalNumberHandler *roundUp = [NSDecimalNumberHandler decimalNumberHandlerWithRoundingMode:NSRoundBankers scale:scale raiseOnExactness:NO raiseOnOverflow:NO raiseOnUnderflow:NO raiseOnDivideByZero:YES];
    NSDecimalNumber *sourceDecimalNumber = [NSDecimalNumber decimalNumberWithString:sourceString];
    sourceDecimalNumber = [sourceDecimalNumber decimalNumberByRoundingAccordingToBehavior:roundUp];
    NSString *numberString = sourceDecimalNumber.stringValue;
    NSRange range = [numberString rangeOfString:@"."];
    if (range.length == 0) {
        numberString = [numberString stringByAppendingString:@"."];
        for (NSInteger i = 0; i < scale; i++) {
            numberString = [numberString stringByAppendingString:@"0"];
        }
    } else {
        NSInteger addZeroCount = scale - (numberString.length - range.location - 1);
        for (NSInteger i = 0; i < addZeroCount; i++) {
            numberString = [numberString stringByAppendingString:@"0"];
        }
    }
    return numberString;
}

@end
