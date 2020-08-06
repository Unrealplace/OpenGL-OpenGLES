//
//  NSDate+MPMUtils.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/25.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

#define D_MINUTE 60
#define D_HOUR   3600
#define D_DAY    86400
#define D_WEEK   604800
#define D_YEAR   31556926

NS_ASSUME_NONNULL_BEGIN

@interface NSDate (MPMUtils)

+ (NSDate *)dateWithYear:(NSInteger)year
                   month:(NSInteger)month
                     day:(NSInteger)day
                    hour:(NSInteger)hour
                  minute:(NSInteger)minute
                  second:(NSInteger)second toDate:(NSDate *)date;

+ (NSInteger)daysOffsetBetweenStartDate:(NSDate *)startDate endDate:(NSDate *)endDate;

+ (NSDate *)dateWithHour:(int)hour
                  minute:(int)minute;

#pragma mark - Getter
- (NSInteger)year;
- (NSInteger)month;
- (NSInteger)day;
- (NSInteger)hour;
- (NSInteger)minute;
- (NSInteger)second;
- (NSString *)weekday;

#pragma mark - Time string
- (NSString *)timeHourMinute;
- (NSString *)timeHourMinuteWithPrefix;
- (NSString *)timeHourMinuteWithSuffix;
- (NSString *)timeHourMinuteWithPrefix:(BOOL)enablePrefix suffix:(BOOL)enableSuffix;

- (NSString *)stringYearMonthDayCompareTodayForTimeLine;

#pragma mark - Date String
- (NSString *)stringTime;
- (NSString *)stringMonthDay;
- (NSString *)stringYearMonthDay;
- (NSString *)stringYearMonthDayHourMinuteSecond;
+ (NSString *)stringYearMonthDayWithDate:(NSDate *)date;      //date为空时返回的是当前年月日
+ (NSString *)stringLoacalDate;

#pragma mark - Date formate
+ (NSString *)dateFormatString;
+ (NSString *)timeFormatString;
+ (NSString *)timestampFormatString;
+ (NSString *)timestampFormatStringSubSeconds;
- (NSString *)dateStringWithFormat:(NSString *)format;
/// yyyy-MM-dd HH:mm:ss日期格式
- (NSString *)dateStringFull;

#pragma mark - Date adjust
- (NSDate *) dateByAddingDays: (NSInteger) dDays;
- (NSDate *) dateBySubtractingDays: (NSInteger) dDays;

#pragma mark - Relative dates from the date
+ (NSDate *) dateTomorrow;
+ (NSDate *) dateYesterday;
+ (NSDate *) dateWithDaysFromNow: (NSInteger) days;
+ (NSDate *) dateWithDaysBeforeNow: (NSInteger) days;
+ (NSDate *) dateWithHoursFromNow: (NSInteger) dHours;
+ (NSDate *) dateWithHoursBeforeNow: (NSInteger) dHours;
+ (NSDate *) dateWithMinutesFromNow: (NSInteger) dMinutes;
+ (NSDate *) dateWithMinutesBeforeNow: (NSInteger) dMinutes;

// 标准格式的零点日期
+ (NSDate *) dateStandardFormatTimeZeroWithDate: (NSDate *) aDate;
// 负数为过去，正数为未来
- (NSInteger) daysBetweenCurrentDateAndDate;

- (NSString *)stringMonthDayForTimeLine;
- (NSString *)stringYearMonthDayForTimeLine;

#pragma mark - Date compare
- (BOOL)isEqualToDateIgnoringTime:(NSDate *)aDate;
// 返回“今天”，“明天”，“昨天”，或年月日
- (NSString *)stringYearMonthDayCompareToday;

// 判断某时间是否在特定时间之前
+ (BOOL)checkTime:(NSDate *)time isBeforeTempTime:(NSDate *)tempTime;

// 判断时间是否为今天
+ (BOOL)isToday:(NSDate *)date;

// 判断当前时间是否在开始和结束时间之间
+ (BOOL)timeBetweenBeginTime:(NSString *)beginTime endTime:(NSString *)endTime;

#pragma mark - Date and string convert
+ (NSDate *)dateFromString:(NSString *)string;
+ (NSDate *)dateFromString:(NSString *)string withFormat:(NSString *)format;
- (NSString *)string;
- (NSString *)stringCutSeconds;
/// 本地化时间
- (NSString *)localTimeString;

+ (NSString *)stringFromTimeStamp:(NSString *)timeStamp;

@end

NS_ASSUME_NONNULL_END
