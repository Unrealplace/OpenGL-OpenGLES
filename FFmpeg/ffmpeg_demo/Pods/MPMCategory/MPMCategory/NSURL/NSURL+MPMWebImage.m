//
//  NSURL+MPMWebImage.m
//  MPMCategorys
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "NSURL+MPMWebImage.h"

#import <SDWebImage/SDWebImageManager.h>
#import <SDWebImage/UIImage+MultiFormat.h>
#import <SDWebImage/SDWebImageGIFCoder.h>
#import <SDWebImage/SDWebImageCodersManager.h>

@implementation NSURL (MPMWebImage)

- (void)webImageCompletionBlock:(WebImagecompletionBlock)block {
    if (![[[SDWebImageCodersManager sharedInstance] coders] containsObject:[SDWebImageGIFCoder sharedCoder]]) {
        [[SDWebImageCodersManager sharedInstance] addCoder:[SDWebImageGIFCoder sharedCoder]];
    }
    [[SDWebImageManager sharedManager] loadImageWithURL:self options:0 progress:nil completed:^(UIImage * _Nullable image, NSData * _Nullable data, NSError * _Nullable error, SDImageCacheType cacheType, BOOL finished, NSURL * _Nullable imageURL) {
        if (data) {
            image = [UIImage sd_imageWithData:data];
        }
        if (block) {
            block(image,data);
        }
    }];
}

@end
