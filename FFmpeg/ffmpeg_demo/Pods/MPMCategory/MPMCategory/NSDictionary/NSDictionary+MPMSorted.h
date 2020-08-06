//
//  NSDictionary+MPMSorted.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary (MPMSorted)

/**
 *  排序时默认不忽略大小写
 *  @param type 排序方式:升序或者降序
 */
- (NSString *)sortedStringByComparisonType:(NSComparisonResult)type;

@end

NS_ASSUME_NONNULL_END
