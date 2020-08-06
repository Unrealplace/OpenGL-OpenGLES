//
//  NSDate+MPMUtils.m
//  MPMCategorys
//
//  Created by Done.L on 2019/6/25.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSDate+MPMUtils.h"

#define DATE_COMPONENTS (NSCalendarUnitYear| NSCalendarUnitMonth | NSCalendarUnitDay | NSCalendarUnitWeekOfMonth |  NSCalendarUnitHour | NSCalendarUnitMinute | NSCalendarUnitSecond | NSCalendarUnitWeekday | NSCalendarUnitWeekdayOrdinal)
#define CURRENT_CALENDAR [NSCalendar currentCalendar]

@implementation NSDate (MPMUtils)

+ (NSDate *)dateWithYear:(NSInteger)year
                   month:(NSInteger)month
                     day:(NSInteger)day
                    hour:(NSInteger)hour
                  minute:(NSInteger)minute
                  second:(NSInteger)second toDate:(NSDate *)date {
    NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
    
    NSTimeZone *systemTimeZone = [NSTimeZone systemTimeZone];
    
    NSDateComponents *dateComps = [[NSDateComponents alloc] init];
    [dateComps setCalendar:calendar];
    [dateComps setYear:year];
    [dateComps setMonth:month];
    [dateComps setDay:day];
    [dateComps setTimeZone:systemTimeZone];
    [dateComps setHour:hour];
    [dateComps setMinute:minute];
    [dateComps setSecond:second];
    
    NSDate *nextData = [calendar dateByAddingComponents:dateComps toDate:date options:NSCalendarMatchStrictly];
    
    return nextData;
}

+ (NSInteger)daysOffsetBetweenStartDate:(NSDate *)startDate endDate:(NSDate *)endDate {
    NSCalendar *gregorian = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
    unsigned int unitFlags = NSCalendarUnitDay;
    NSDateComponents *comps = [gregorian components:unitFlags fromDate:startDate  toDate:endDate  options:0];
    NSInteger days = [comps day];
    return days;
}

+ (NSDate *)dateWithHour:(int)hour minute:(int)minute {
    NSDate *now = [NSDate date];
    NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSCalendarIdentifierGregorian];
    NSDateComponents *components = [calendar components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay fromDate:now];
    [components setHour:hour];
    [components setMinute:minute];
    NSDate *newDate = [calendar dateFromComponents:components];
    return newDate;
}

#pragma mark - Data component

- (NSInteger)year {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute fromDate:self];
    return [dateComponents year];
}

- (NSInteger)month {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute fromDate:self];
    return [dateComponents month];
}

- (NSInteger)day {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute fromDate:self];
    return [dateComponents day];
}

- (NSInteger)hour {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute  fromDate:self];
    return [dateComponents hour];
}

- (NSInteger)minute {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute  fromDate:self];
    return [dateComponents minute];
}

- (NSInteger)second {
    NSDateComponents *dateComponents = [[NSCalendar currentCalendar] components:NSCalendarUnitYear|NSCalendarUnitMonth|NSCalendarUnitDay|NSCalendarUnitHour|NSCalendarUnitMinute  fromDate:self];
    return [dateComponents second];
}

- (NSString *)weekday {
    NSCalendar *calendar = [NSCalendar currentCalendar];
    NSDateComponents *comps;
    
    NSDate *date = [NSDate date];
    comps =[calendar components:(NSCalendarUnitWeekOfMonth | NSCalendarUnitWeekOfMonth |NSCalendarUnitWeekdayOrdinal)
                       fromDate:date];
    NSInteger weekday = [comps weekday]; // 星期几（注意，周日是“1”，周一是“2”。。。。）
    NSString *week = @"";
    switch (weekday) {
        case 1:
            week = @"星期日";
        break;
            
        case 2:
            week = @"星期一";
        break;
            
        case 3:
            week = @"星期二";
        break;
            
        case 4:
            week = @"星期三";
        break;
            
        case 5:
            week = @"星期四";
        break;
            
        case 6:
            week = @"星期五";
        break;
            
        case 7:
            week = @"星期六";
        break;
            
        default:
            break;
    }
    
    return week;
}

#pragma mark - Time string
- (NSString *)timeHourMinute {
    return [self timeHourMinuteWithPrefix:NO suffix:NO];
}

- (NSString *)timeHourMinuteWithPrefix {
    return [self timeHourMinuteWithPrefix:YES suffix:NO];
}

- (NSString *)timeHourMinuteWithSuffix {
    return [self timeHourMinuteWithPrefix:NO suffix:YES];
}

- (NSString *)timeHourMinuteWithPrefix:(BOOL)enablePrefix suffix:(BOOL)enableSuffix {
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"HH:mm"];
    NSString *timeStr = [formatter stringFromDate:self];
    if (enablePrefix) {
        timeStr = [NSString stringWithFormat:@"%@%@",([self hour] > 12 ? @"下午" : @"上午"),timeStr];
    }
    if (enableSuffix) {
        timeStr = [NSString stringWithFormat:@"%@%@",([self hour] > 12 ? @"pm" : @"am"),timeStr];
    }
    return timeStr;
}

#pragma mark - Date String
- (NSString *)stringTime {
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"HH:mm"];
    NSString *str = [formatter stringFromDate:self];
    return str;
}

- (NSString *)stringMonthDay {
    return [NSDate dateMonthDayWithDate:self];
}

- (NSString *)stringMonthDayForTimeLine {
    return [NSDate dateMonthDayWithDateForTimeLine:self];
}

- (NSString *)stringYearMonthDay {
    return [NSDate stringYearMonthDayWithDate:self];
}

- (NSString *)stringYearMonthDayForTimeLine {
    return [NSDate stringYearMonthDayWithDateForTimeline:self];
}

- (NSString *)stringYearMonthDayHourMinuteSecond {
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"MM-dd HH:mm:ss"];
    NSString *str = [formatter stringFromDate:self];
    return str;
}

- (NSString *)stringYearMonthDayCompareTodayForTimeLine {
    NSString *str;
    NSInteger chaDay = [self daysBetweenCurrentDateAndDate];
    if (chaDay == 0) {
        str = @"今天";
    } else if (chaDay == 1) {
        str = @"明天";
    } else if (chaDay == -1) {
        str = @"昨天";
    } else {
        str = [self stringYearMonthDayForTimeLine];
    }
    
    return str;
}

- (NSString *)stringYearMonthDayCompareToday {
    NSString *str;
    NSInteger chaDay = [self daysBetweenCurrentDateAndDate];
    if (chaDay == 0) {
        str = @"今天";
    } else if (chaDay == 1) {
        str = @"明天";
    } else if (chaDay == -1) {
        str = @"昨天";
    } else {
        str = [self dateStringWithFormat:@"M月d日"];
    }
    
    return str;
}

+ (NSString *)stringLoacalDate {
    NSDateFormatter *format = [[NSDateFormatter alloc] init];
    [format setTimeZone:[NSTimeZone timeZoneWithAbbreviation:@"UTC"]];
    [format  setDateFormat:@"MM-dd HH:mm:ss"];
    NSDate *date = [NSDate date];
    NSTimeZone *zone = [NSTimeZone systemTimeZone];
    NSInteger interval = [zone secondsFromGMTForDate: date];
    NSDate *localeDate = [date  dateByAddingTimeInterval: interval];
    NSString *dateStr = [format stringFromDate:localeDate];
    
    return dateStr;
}

+ (NSString *)stringYearMonthDayWithDate:(NSDate *)date {
    if (date == nil) {
        date = [NSDate date];
    }
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"MM-dd"];
    NSString *str = [formatter stringFromDate:date];
    return str;
}

+ (NSString *)stringYearMonthDayWithDateForTimeline:(NSDate *)date {
    if (date == nil) {
        date = [NSDate date];
    }
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"]];
    
    [formatter setDateFormat:@"dd-M月"];
    NSString *str = [formatter stringFromDate:date];
    return str;
}

+ (NSString *)dateMonthDayWithDate:(NSDate *)date {
    if (date == nil) {
        date = [NSDate date];
    }
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setDateFormat:@"M月d日"];
    NSString *str = [formatter stringFromDate:date];
    return str;
}

+ (NSString *)dateMonthDayWithDateForTimeLine:(NSDate *)date {
    if (date == nil) {
        date = [NSDate date];
    }
    
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"]];
    [formatter setDateFormat:@"dd-M月"];
    NSString *str = [formatter stringFromDate:date];
    return str;
}

#pragma mark - Date formate

+ (NSString *)dateFormatString {
    return @"MM-dd";
}

+ (NSString *)timeFormatString {
    return @"HH:mm:ss";
}

+ (NSString *)timestampFormatString {
    return @"MM-dd HH:mm:ss";
}

+ (NSString *)timestampFormatStringSubSeconds {
    return @"MM-dd HH:mm";
}

- (NSString *)dateStringWithFormat:(NSString *)format {
    NSDateFormatter *formatter = [[NSDateFormatter alloc]init];
    [formatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"zh_CN"]];
    [formatter setDateFormat:format];
    NSString *str = [formatter stringFromDate:self];
    return str;
}

- (NSString *)dateStringFull {
    return [self dateStringWithFormat:@"yyyy-MM-dd HH:mm:ss"];
}

#pragma mark - Date adjust
- (NSDate *)dateByAddingDays:(NSInteger)dDays {
    NSTimeInterval aTimeInterval = [self timeIntervalSinceReferenceDate] + D_DAY * dDays;
    NSDate *newDate = [NSDate dateWithTimeIntervalSinceReferenceDate:aTimeInterval];
    return newDate;
}

- (NSDate *)dateBySubtractingDays:(NSInteger)dDays {
    return [self dateByAddingDays: (dDays * -1)];
}

#pragma mark - Relative Dates
+ (NSDate *)dateWithDaysFromNow:(NSInteger)days {
    return [[NSDate date] dateByAddingDays:days];
}

+ (NSDate *)dateWithDaysBeforeNow:(NSInteger)days {
    return [[NSDate date] dateBySubtractingDays:days];
}

+ (NSDate *)dateTomorrow {
    return [NSDate dateWithDaysFromNow:1];
}

+ (NSDate *)dateYesterday {
    return [NSDate dateWithDaysBeforeNow:1];
}

+ (NSDate *)dateWithHoursFromNow:(NSInteger)dHours {
    NSTimeInterval aTimeInterval = [[NSDate date] timeIntervalSinceReferenceDate] + D_HOUR * dHours;
    NSDate *newDate = [NSDate dateWithTimeIntervalSinceReferenceDate:aTimeInterval];
    return newDate;
}

+ (NSDate *)dateWithHoursBeforeNow:(NSInteger)dHours {
    NSTimeInterval aTimeInterval = [[NSDate date] timeIntervalSinceReferenceDate] - D_HOUR * dHours;
    NSDate *newDate = [NSDate dateWithTimeIntervalSinceReferenceDate:aTimeInterval];
    return newDate;
}

+ (NSDate *)dateWithMinutesFromNow:(NSInteger)dMinutes {
    NSTimeInterval aTimeInterval = [[NSDate date] timeIntervalSinceReferenceDate] + D_MINUTE * dMinutes;
    NSDate *newDate = [NSDate dateWithTimeIntervalSinceReferenceDate:aTimeInterval];
    return newDate;
}

+ (NSDate *)dateWithMinutesBeforeNow:(NSInteger)dMinutes {
    NSTimeInterval aTimeInterval = [[NSDate date] timeIntervalSinceReferenceDate] - D_MINUTE * dMinutes;
    NSDate *newDate = [NSDate dateWithTimeIntervalSinceReferenceDate:aTimeInterval];
    return newDate;
}

- (BOOL) isEqualToDateIgnoringTime:(NSDate *)aDate {
    NSDateComponents *components1 = [CURRENT_CALENDAR components:DATE_COMPONENTS fromDate:self];
    NSDateComponents *components2 = [CURRENT_CALENDAR components:DATE_COMPONENTS fromDate:aDate];
    return ((components1.year == components2.year) &&
            (components1.month == components2.month) &&
            (components1.day == components2.day));
}

+ (NSDate *)dateStandardFormatTimeZeroWithDate:(NSDate *)aDate {
    NSString *str = [[NSDate stringYearMonthDayWithDate:aDate] stringByAppendingString:@" 00:00:00"];
    NSDate *date = [NSDate dateFromString:str];
    return date;
}

// 判断当前时间是否在开始和结束时间之间
+ (BOOL)timeBetweenBeginTime:(NSString *)beginTime endTime:(NSString *)endTime {
    if (!beginTime || !endTime) {
        return NO;
    }
    NSDate *timeDate =  [NSDate dateWithTimeIntervalSinceNow:0];
    
    NSDate *beginDate = [NSDate dateWithTimeIntervalSince1970:[beginTime doubleValue] / 1000];
    if (beginTime.length == 10) {
        beginDate = [NSDate dateWithTimeIntervalSince1970:[beginTime doubleValue]];
    }
    NSDate *endDate = [NSDate dateWithTimeIntervalSince1970:[endTime doubleValue] / 1000];
    if (endTime.length == 10) {
        endDate = [NSDate dateWithTimeIntervalSince1970:[endTime doubleValue]];
    }
    
    if ([timeDate compare:beginDate] == NSOrderedAscending  || [timeDate compare:endDate] == NSOrderedDescending ) {
        return NO;
    }
    return YES;
}

+ (BOOL)checkTime:(NSDate *)time isBeforeTempTime:(NSDate *)tempTime {
    // 判断time是否在tempTime之前
    if ([time isEqualToDate:tempTime]) {
        return NO;
    }
    if ([time earlierDate:tempTime] == time) {
        return YES;
    } else {
        return NO;
    }
}

// 判断时间是否为今天
+ (BOOL)isToday:(NSDate *)date {
    NSDate *today = [NSDate dateWithTimeIntervalSinceNow:8*60*60];
    NSString * todayString = [[today description] substringToIndex:10];
    NSString * dateString = [[date description] substringToIndex:10];
    if ([todayString isEqualToString:dateString]) {
        return YES;
    } else {
        return NO;
    }
}

- (NSInteger) daysBetweenCurrentDateAndDate {
    // 只取年月日比较
    NSDate *dateSelf = [NSDate dateStandardFormatTimeZeroWithDate:self];
    NSTimeInterval timeInterval = [dateSelf timeIntervalSince1970];
    NSDate *dateNow = [NSDate dateStandardFormatTimeZeroWithDate:nil];
    NSTimeInterval timeIntervalNow = [dateNow timeIntervalSince1970];
    
    NSTimeInterval cha = timeInterval - timeIntervalNow;
    CGFloat chaDay = cha / 86400.0;
    NSInteger day = chaDay * 1;
    return day;
}

#pragma mark - Date and string convert
+ (NSDate *)dateFromString:(NSString *)string {
    return [NSDate dateFromString:string withFormat:[NSDate dbFormatString]];
}

+ (NSDate *)dateFromString:(NSString *)string withFormat:(NSString *)format {
    NSDateFormatter *inputFormatter = [[NSDateFormatter alloc] init];
    [inputFormatter setDateFormat:format];
    NSDate *date = [inputFormatter dateFromString:string];
    return date;
}

- (NSString *)string {
    return [self stringWithFormat:[NSDate dbFormatString]];
}

- (NSString *)stringCutSeconds {
    return [self stringWithFormat:[NSDate timestampFormatStringSubSeconds]];
}

- (NSString *)stringWithFormat:(NSString *)format {
    NSDateFormatter *outputFormatter = [[NSDateFormatter alloc] init];
    [outputFormatter setDateFormat:format];
    NSString *timestamp_str = [outputFormatter stringFromDate:self];
    return timestamp_str;
}

+ (NSString *)dbFormatString {
    return [NSDate timestampFormatString];
}

- (NSString *)localTimeString {
    NSDate *localLastDate = self;
    
    NSString *dateStr;  //年月日
    NSString *period;   //时间段
    NSString *hour;     //时
    
    if ([localLastDate year]==[[NSDate date] year]) {
        NSInteger days = [NSDate daysOffsetBetweenStartDate:localLastDate endDate:[NSDate date]];
        if (days <= 2) {
            dateStr = [localLastDate stringYearMonthDayCompareToday];
        } else {
            dateStr = [localLastDate stringMonthDay];
        }
    } else {
        dateStr = [localLastDate stringYearMonthDay];
    }
    
    
    if ([localLastDate hour]>=5 && [localLastDate hour]<12) {
        period = @"上午";
        hour = [NSString stringWithFormat:@"%02d",(int)[localLastDate hour]];
    } else if ([localLastDate hour]>=12 && [localLastDate hour]<=18){
        period = @"下午";
        hour = [NSString stringWithFormat:@"%02d",(int)[localLastDate hour]];
    } else if ([localLastDate hour]>18 && [localLastDate hour]<=23){
        period = @"晚上";
        hour = [NSString stringWithFormat:@"%02d",(int)[localLastDate hour]];
    } else {
        period = @"凌晨";
        hour = [NSString stringWithFormat:@"%02d",(int)[localLastDate hour]];
    }
    return [NSString stringWithFormat:@"%@ %@ %@:%02d",dateStr,period,hour,(int)[localLastDate minute]];
    
}

+ (NSString *)stringFromTimeStamp:(NSString *)timeStamp {
    NSString *result = nil;
    
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:[timeStamp longLongValue] / 1000];
    if (date) {
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        [formatter setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
        result = [formatter stringFromDate:date];
    }
    
    return result;
}

@end
