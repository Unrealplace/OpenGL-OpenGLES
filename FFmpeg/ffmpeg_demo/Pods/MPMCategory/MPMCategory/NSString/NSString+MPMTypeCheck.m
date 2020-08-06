//
//  NSString+MPMTypeCheck.m
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSString+MPMTypeCheck.h"

@implementation NSString (MPMTypeCheck)

+ (BOOL)isBlankString:(NSString *)string {
    if (string == nil || [string isEqual:[NSNull null]] || ![string isKindOfClass:[NSString class]] ||string.length == 0 || [string isEqualToString:@""] || [string isEqualToString:@"<null>"] || [string isEqualToString:@"(null)"]) {
        return YES;
    }
    
    NSString *theStr = [self removeEndSpaceFrom:string];
    if (theStr.length == 0 || [theStr isEqualToString:@""]) {
        return YES;
    }
    
    NSString *subStr = [self removeLineFeedFrom:string];
    if (subStr.length == 0 || [subStr isEqualToString:@""]) {
        return YES;
    }
    return NO;
}

+ (NSString *)removeLineFeedFrom:(NSString *)headerData {
    //A character set containing only the whitespace characters space (U+0020) and tab (U+0009) and the newline and nextline characters (U+000A–U+000D, U+0085).
    headerData = [headerData stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];  //去除掉首尾的空白字符和换行字符
    headerData = [headerData stringByReplacingOccurrencesOfString:@"\r" withString:@""];
    headerData = [headerData stringByReplacingOccurrencesOfString:@"\n" withString:@""];
    return headerData;
}

+ (NSString *)removeEndSpaceFrom:(NSString *)strtoremove {
    NSUInteger location = 0;
    unichar charBuffer[[strtoremove length]];
    [strtoremove getCharacters:charBuffer];
    NSUInteger i = 0;
    for ( i = [strtoremove length]; i >0; i--){
        if (![[NSCharacterSet whitespaceCharacterSet] characterIsMember:charBuffer[i - 1]]){
            break;
        }
    }
    return  [strtoremove substringWithRange:NSMakeRange(location, i  - location)];
}

+ (BOOL)isValidatePasswrod:(NSString *)password {
    NSString *passwordRegex = @"[a-zA-Z0-9\\.,\\?\\':…/;\"!\\(\\)\\*&\\[\\]\\\\`~#$%^_\\+-=\\{\\}\\|\\<\\>\\@]{6,20}";
    NSPredicate *passwordTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", passwordRegex];
    return [passwordTest evaluateWithObject:password];
}

+ (BOOL)isContainsString:(NSString *)parentString subString:(NSString *)subString {
    if(parentString == nil || subString == nil)
        return NO;
    NSRange range = [parentString rangeOfString:subString];
    return range.location != NSNotFound;
}

+ (BOOL)stringContainsEmoji:(NSString *)string {
    __block BOOL returnValue = NO;
    [string enumerateSubstringsInRange:NSMakeRange(0, [string length])
                               options:NSStringEnumerationByComposedCharacterSequences
                            usingBlock:^(NSString * _Nullable substring, NSRange substringRange, NSRange enclosingRange, BOOL * _Nonnull stop) {
                                const unichar hs = [substring characterAtIndex:0];
                                if (0xd800 <= hs && hs <= 0xdbff) {
                                    if (substring.length > 1) {
                                        const unichar ls = [substring characterAtIndex:1];
                                        const int uc = ((hs - 0xd800) * 0x400) + (ls - 0xdc00) + 0x10000;
                                        if (0x1d000 <= uc && uc <= 0x1f9ff) {
                                            returnValue = YES;
                                        }
                                    }
                                } else if (substring.length > 1) {
                                    const unichar ls = [substring characterAtIndex:1];
                                    if (ls == 0x20e3 || ls == 0xFE0F || ls == 0xd83c) {
                                        returnValue = YES;
                                    }
                                } else {
                                    if (0x2100 <= hs && hs <= 0x27ff) {
                                        if (0x278b <= hs && 0x2792 >= hs) {
                                            returnValue = NO;
                                        }else {
                                            returnValue = YES;
                                        }
                                    } else if (0x2B05 <= hs && hs <= 0x2b07) {
                                        returnValue = YES;
                                    } else if (0x2934 <= hs && hs <= 0x2935) {
                                        returnValue = YES;
                                    } else if (0x3297 <= hs && hs <= 0x3299) {
                                        returnValue = YES;
                                    } else if (hs == 0xa9 || hs == 0xae || hs == 0x303d || hs == 0x3030 || hs == 0x2b55 || hs == 0x2b1c || hs == 0x2b1b || hs == 0x2b50 || hs == 0xd83e) {
                                        returnValue = YES;
                                    }
                                }
                            }];
    
    return returnValue;
}


+ (BOOL)validateIDCardNumber:(NSString *)value {
    value = [value stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    if ([NSString isBlankString:value]) {
        return NO;
    }
    
    NSUInteger length = value.length;
    if (length != 15 && length !=18) {
        return NO;
    }
    
    // 省份代码
    NSArray *areasArray =@[@"11",@"12", @"13",@"14", @"15",@"21", @"22",@"23", @"31",@"32", @"33",@"34", @"35",@"36", @"37",@"41", @"42",@"43", @"44",@"45", @"46",@"50", @"51",@"52", @"53",@"54", @"61",@"62", @"63",@"64", @"65",@"71", @"81",@"82", @"91"];
    
    NSString *valueStart2 = [value substringToIndex:2];
    BOOL areaFlag = NO;
    for (NSString *areaCode in areasArray) {
        if ([areaCode isEqualToString:valueStart2]) {
            areaFlag =YES;
            break;
        }
    }
    
    if (!areaFlag) {
        return false;
    }
    
    NSRegularExpression *regularExpression;
    NSUInteger numberofMatch;
    
    int year = 0;
    switch (length) {
        case 15:
            year = [value substringWithRange:NSMakeRange(6,2)].intValue + 1900;
            if (year % 4 == 0 || (year % 100 == 0 && year % 4 == 0)) {
                regularExpression = [[NSRegularExpression alloc]initWithPattern:@"^[1-9][0-9]{5}[0-9]{2}((01|03|05|07|08|10|12)(0[1-9]|[1-2][0-9]|3[0-1])|(04|06|09|11)(0[1-9]|[1-2][0-9]|30)|02(0[1-9]|[1-2][0-9]))[0-9]{3}$"
                                                                        options:NSRegularExpressionCaseInsensitive
                                                                          error:nil];//测试出生日期的合法性
            } else {
                regularExpression = [[NSRegularExpression alloc]initWithPattern:@"^[1-9][0-9]{5}[0-9]{2}((01|03|05|07|08|10|12)(0[1-9]|[1-2][0-9]|3[0-1])|(04|06|09|11)(0[1-9]|[1-2][0-9]|30)|02(0[1-9]|1[0-9]|2[0-8]))[0-9]{3}$"
                                                                        options:NSRegularExpressionCaseInsensitive
                                                                          error:nil];//测试出生日期的合法性
            }
            
            numberofMatch = [regularExpression numberOfMatchesInString:value
                                                               options:NSMatchingReportProgress
                                                                 range:NSMakeRange(0, value.length)];
            if (numberofMatch > 0) {
                return YES;
            } else {
                return NO;
            }
            
        case 18:
            year = [value substringWithRange:NSMakeRange(6,4)].intValue;
            if (year % 4 == 0 || (year % 100 == 0 && year % 4 == 0)) {
                regularExpression = [[NSRegularExpression alloc]initWithPattern:@"^[1-9][0-9]{5}(19|20)[0-9]{2}((01|03|05|07|08|10|12)(0[1-9]|[1-2][0-9]|3[0-1])|(04|06|09|11)(0[1-9]|[1-2][0-9]|30)|02(0[1-9]|[1-2][0-9]))[0-9]{3}[0-9Xx]$"
                                                                        options:NSRegularExpressionCaseInsensitive
                                                                          error:nil];//测试出生日期的合法性
            } else {
                regularExpression = [[NSRegularExpression alloc]initWithPattern:@"^[1-9][0-9]{5}(19|20)[0-9]{2}((01|03|05|07|08|10|12)(0[1-9]|[1-2][0-9]|3[0-1])|(04|06|09|11)(0[1-9]|[1-2][0-9]|30)|02(0[1-9]|1[0-9]|2[0-8]))[0-9]{3}[0-9Xx]$"
                                                                        options:NSRegularExpressionCaseInsensitive
                                                                          error:nil];//测试出生日期的合法性
            }
            
            numberofMatch = [regularExpression numberOfMatchesInString:value
                                                               options:NSMatchingReportProgress
                                                                 range:NSMakeRange(0, value.length)];
            
            if (numberofMatch > 0) {
                int S = ([value substringWithRange:NSMakeRange(0,1)].intValue + [value substringWithRange:NSMakeRange(10,1)].intValue) *7 + ([value substringWithRange:NSMakeRange(1,1)].intValue + [value substringWithRange:NSMakeRange(11,1)].intValue) *9 + ([value substringWithRange:NSMakeRange(2,1)].intValue + [value substringWithRange:NSMakeRange(12,1)].intValue) *10 + ([value substringWithRange:NSMakeRange(3,1)].intValue + [value substringWithRange:NSMakeRange(13,1)].intValue) *5 + ([value substringWithRange:NSMakeRange(4,1)].intValue + [value substringWithRange:NSMakeRange(14,1)].intValue) *8 + ([value substringWithRange:NSMakeRange(5,1)].intValue + [value substringWithRange:NSMakeRange(15,1)].intValue) *4 + ([value substringWithRange:NSMakeRange(6,1)].intValue + [value substringWithRange:NSMakeRange(16,1)].intValue) *2 + [value substringWithRange:NSMakeRange(7,1)].intValue *1 + [value substringWithRange:NSMakeRange(8,1)].intValue *6 + [value substringWithRange:NSMakeRange(9,1)].intValue *3;
                
                int Y = S %11;
                NSString *M =@"F";
                NSString *JYM =@"10X98765432";
                M = [JYM substringWithRange:NSMakeRange(Y,1)];// 判断校验位
                
                if ([M caseInsensitiveCompare:[value substringWithRange:NSMakeRange(17,1)]] == NSOrderedSame){
                    return YES;// 检测ID的校验位
                } else {
                    return NO;
                }
                
            } else {
                return NO;
            }
            
        default:
            return false;
    }
}

+ (BOOL)isNumber:(NSString *)aString {
    if ([self isBlankString:aString]) {
        return NO;
    }
    NSString *regex = @"^\\d+(\\.\\d+)?$";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [pred evaluateWithObject:aString];
}

+ (BOOL)isPhoneNumber:(NSString *)phone {
    if ([self isBlankString:phone]) {
        return NO;
    }
    
    NSString *regex = @"^((13([0-9]))|(14([0-9]))|(15([0-9]))|(16([0-9]))|(17([0-9]))|(18([0-9]))|(19([0-9])))\\d{8}$";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [pred evaluateWithObject:phone];
}

+ (BOOL)isFixedTelephone:(NSString *)phone {
    if ([self isBlankString:phone]) {
        return NO;
    }
    
    NSString *regex = @"^(0[0-9]{2})\\d{8}$|^(0[0-9]{3}(\\d{7,8}))$";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [pred evaluateWithObject:phone];
}

+ (BOOL)isLetterOrNumber:(NSString *)aString {
    if ([self isBlankString:aString]) {
        return NO;
    }
    NSString *regex = @"^[a-zA-Z0-9]*$";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [pred evaluateWithObject:aString];
}

+ (BOOL)isPureFloat:(NSString *)string {
    NSScanner *scan = [NSScanner scannerWithString:string];
    float val;
    return [scan scanFloat:&val] && [scan isAtEnd];
}

+ (BOOL)validateLess2FloatString:(NSString *)string {
    NSString *phoneRegex = @"^[0-9]+(\\.[0-9]{1,2})?$";
    NSPredicate *phoneTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",phoneRegex];
    return [phoneTest evaluateWithObject:string];
}

+ (BOOL)checkDecimal:(NSRange)range decimalCount:(NSInteger)decimalCount decimal:(NSString *)decimal {
    BOOL haveDot = NO;
    
    if (decimalCount < 0) {
        decimalCount = 0;
    }
    
    if ([decimal rangeOfString:@"."].location == NSNotFound) {
        haveDot = NO;
    } else {
        haveDot = YES;
    }
    
    if (haveDot) {
        NSRange ran = [decimal rangeOfString:@"."];
        if (range.location - ran.location > decimalCount) {
            return NO;
        }
    }
    
    return YES;
}

+ (BOOL)isValidChinese:(NSString *)string {
    NSString *regex = @"^[\u4e00-\u9fa5]+$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    
    return [predicate evaluateWithObject:string];
}

+ (BOOL)isAlipayAccount:(NSString *)string {
    NSString *regex = @"^[a-z0-9@.]+$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [predicate evaluateWithObject:string];
}

+ (NSRange)rangeOfwwwString:(NSString *)string {
    if (string.length > 0) {
        // 截取发布消息中的网址
        NSError *error;
        NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"((http[s]{0,1}|ftp)://[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)" options:0 error:&error];
        if (regex != nil) {
            NSTextCheckingResult *firstMatch = [regex firstMatchInString:string options:0 range:NSMakeRange(0, [string length])];
            if (firstMatch) {
                NSRange resultResult = [firstMatch rangeAtIndex:0];
                return resultResult;
            }
        }
    }
    
    return NSMakeRange(0, 0);
}

+ (BOOL)isContainsChinese:(NSString *)str {
    for(int i=0; i< [str length];i++){
        int a = [str characterAtIndex:i];
        if(a > 0x4e00 && a < 0x9fff) {
            return YES;
        }
    }
    return NO;
}

+ (BOOL)isContainsBlank:(NSString *)str {
    NSString *_string = str;
    NSRange _range = [_string rangeOfString:@" "];
    if (_range.location != NSNotFound) {
        return YES;
    }else {
        return NO;
    }
}

+ (BOOL)isChineseEnglishNumberMix:(NSString *)string {
    if ([self isBlankString:string]) {
        return NO;
    }
    NSString *regex = @"^[a-zA-Z0-9\u4e00-\u9fa5]*$";
    NSPredicate *pred = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [pred evaluateWithObject:string];
}

@end
