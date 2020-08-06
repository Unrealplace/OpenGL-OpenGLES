//
//  NSURL+MPMWebImage.h
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

typedef void(^WebImagecompletionBlock)(UIImage * _Nullable image, NSData * _Nullable data);

NS_ASSUME_NONNULL_BEGIN

@interface NSURL (MPMWebImage)

- (void)webImageCompletionBlock:(WebImagecompletionBlock)block;

@end

NS_ASSUME_NONNULL_END
