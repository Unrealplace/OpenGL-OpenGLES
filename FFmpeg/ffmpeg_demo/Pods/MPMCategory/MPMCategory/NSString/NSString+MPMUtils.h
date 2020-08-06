//
//  NSString+MPMUtils.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSString (MPMUtils)

/**
 16进制字符串
 */
- (instancetype)hexString;

/*
 MD5加密
 */
- (instancetype)md5String;

/*
 *  textfield输入，特定需求使用（忽略）
 */
- (NSString *)substringAvoidBreakingUpCharacterSequencesWithRange:(NSRange)range lessValue:(BOOL)lessValue countingNonASCIICharacterAsTwo:(BOOL)countingNonASCIICharacterAsTwo;

/**
 去除空格
 */
+ (NSString *)trimBlankString:(NSString *)str;

/**
 去除掉首尾的空白字符和换行字符
 */
+ (NSString *)whitespaceAndNewline:(NSString *)string;

/**
 获取随机获取唯一字符串
 */
+ (NSString *)getUniqueString;

/**
 中文转拼音，并获取每个字的首字母
 
 @param string 中文
 @return key:pinyin, value:拼音全拼；key:firstLetter, value:每个字的首字母
 */
+ (NSDictionary *)chineseTurnToPinyinAndFirstLetters:(NSString *)string;

/**
 获取每一个中文汉字，在string中的index
 
 @param string 原始字符串
 */
+ (NSArray *)getChineseStringLocation:(NSString *)string;

/**
 获取每一行显示的字符串
 
 @param string 原始字符串
 @param font 文字font
 @param width 宽度
 */
+ (NSArray *)getLinesArrayOfString:(NSString *)string font:(UIFont *)font width:(CGFloat)width;

/**
 属性字符串处理
 
 @param originStr 原始字符串
 @param containStr 处理字符串
 @param attributes 属性
 @param range 范围
 */
+ (NSMutableAttributedString *)withString:(NSString *)originStr contain:(NSString *)containStr attributes:(NSDictionary *)attributes range:(NSRange )range;

/**
 字符串匹配
 
 @param input 匹配输入的字符串
 @param inputColor 匹配到之后的text颜色
 @param originalString 原始字符串
 @return NSAttributedString对象
 */
+ (NSAttributedString *)matchInput:(NSString *)input matchInputColor:(UIColor *)inputColor originalString:(NSString *)originalString;


/**
 获取字符串字符长度
 */
+ (NSInteger)lengthOfText:(NSString *)text;

/**
 * @brief 把格式化的JSON格式的字符串转换成字典
 * @param jsonString JSON格式的字符串
 * @return 返回字典
 */
+ (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString;

/**
 设置属性字符串
 
 @param string 目标字符串
 @param font 字体
 @param alignment 对齐方式
 @param textColor 文本颜色
 @return 属性字符串
 */
+ (NSMutableAttributedString *)cm_attributeStingWithString:(NSString *)string font:(UIFont *)font alignment:(NSTextAlignment)alignment textColor:(UIColor *)textColor;

@end

NS_ASSUME_NONNULL_END
