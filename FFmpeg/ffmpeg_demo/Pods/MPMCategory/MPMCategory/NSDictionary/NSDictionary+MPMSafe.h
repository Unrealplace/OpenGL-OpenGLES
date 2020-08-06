//
//  NSDictionary+MPMSafe.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary (MPMSafe)

+ (NSDictionary *_Nullable)nullDic:(NSDictionary *_Nullable)myDic;
+ (NSArray *_Nullable)nullArr:(NSArray *_Nullable)myArr;
+ (NSString *_Nullable)stringToString:(NSString *_Nullable)string;
+ (NSString *_Nullable)nullToString;
+ (id _Nullable )changeType:(id _Nullable )myObj;

- (NSString *)stringForKey:(id)key;

- (NSNumber *)numberForKey:(id)key;

- (NSDecimalNumber *)decimalNumberForKey:(id)key;

- (NSArray *)arrayForKey:(id)key;

- (NSDictionary *)dictionaryForKey:(id)key;

- (NSInteger)integerForKey:(id)key;

- (NSUInteger)unsignedIntegerForKey:(id)key;

- (id)objForKey:(id)key;

- (BOOL)boolForKey:(id)key;

- (int16_t)int16ForKey:(id)key;

- (int32_t)int32ForKey:(id)key;

- (int64_t)int64ForKey:(id)key;

- (char)charForKey:(id)key;

- (short)shortForKey:(id)key;

- (float)floatForKey:(id)key;

- (double)doubleForKey:(id)key;

- (long long)longLongForKey:(id)key;

- (unsigned long long)unsignedLongLongForKey:(id)key;

- (NSDate *)dateForKey:(id)key dateFormat:(NSString *)dateFormat;

- (CGFloat)CGFloatForKey:(id)key;

- (CGPoint)pointForKey:(id)key;

- (CGSize)sizeForKey:(id)key;

- (CGRect)rectForKey:(id)key;

@end

#pragma -- mark NSMutableDictionary

@interface NSMutableDictionary(SafeAccess)

- (void)setObj:(id)i forKey:(NSString *)key;

- (void)setString:(NSString *)i forKey:(NSString *)key;

- (void)setBool:(BOOL)i forKey:(NSString *)key;

- (void)setInt:(int)i forKey:(NSString *)key;

- (void)setInteger:(NSInteger)i forKey:(NSString *)key;

- (void)setUnsignedInteger:(NSUInteger)i forKey:(NSString *)key;

- (void)setCGFloat:(CGFloat)f forKey:(NSString *)key;

- (void)setChar:(char)c forKey:(NSString *)key;

- (void)setFloat:(float)i forKey:(NSString *)key;

- (void)setDouble:(double)i forKey:(NSString *)key;

- (void)setLongLong:(long long)i forKey:(NSString *)key;

- (void)setPoint:(CGPoint)point forKey:(NSString *)key;

- (void)setSize:(CGSize)size forKey:(NSString *)key;

- (void)setRect:(CGRect)rect forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
