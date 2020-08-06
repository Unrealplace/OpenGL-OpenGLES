//
//  FFOpenGLRenderView.h
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface FFOpenGLRenderView : UIView

- (void)inputPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
