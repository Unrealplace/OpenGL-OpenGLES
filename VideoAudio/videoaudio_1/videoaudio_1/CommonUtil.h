//
//  CommonUtil.h
//  videoaudio_1
//
//  Created by mpm on 2020/7/30.
//  Copyright © 2020 mpm. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CommonUtil : NSObject

+(NSString *)bundlePath:(NSString *)fileName;

+(NSString *)documentsPath:(NSString *)fileName;


@end

NS_ASSUME_NONNULL_END
