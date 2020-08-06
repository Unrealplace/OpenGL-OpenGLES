//
//  NSDictionary+MPMSorted.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSDictionary+MPMSorted.h"

@implementation NSDictionary (MPMSorted)

- (NSString *)sortedStringByComparisonType: (NSComparisonResult)type {
    NSArray *keyArray = self.allKeys;
    NSArray *sortedKeyArray = [keyArray sortedArrayUsingComparator:^NSComparisonResult(id  _Nonnull obj1, id  _Nonnull obj2) {
        NSAssert([obj1 isKindOfClass:[NSString class]], @"必须使用NSString类型的参数名");
        NSAssert([obj2 isKindOfClass:[NSString class]], @"必须使用NSString类型的参数名");
        
        if (type == NSOrderedAscending) {
            // options:NSCaseInsensitiveSearch
            return [obj1 compare:obj2];
        } else {
            return [obj2 compare:obj1];
        }
    }];
    
    NSMutableString *sortedString = [NSMutableString string];
    for (int i = 0; i < sortedKeyArray.count; i++) {
        NSString *key = sortedKeyArray[i];
        NSString *temp = [NSString stringWithFormat:@"%@=%@&",key,self[key]];
        [sortedString appendString:temp];
    }
    
    [sortedString deleteCharactersInRange:NSMakeRange(sortedString.length - 1, 1)];
    
    return sortedString;
}

@end
