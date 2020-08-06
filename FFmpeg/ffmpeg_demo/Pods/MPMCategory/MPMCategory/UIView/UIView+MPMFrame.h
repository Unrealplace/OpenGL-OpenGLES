//
//  UIView+MPMFrame.h
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

CGPoint CGRectGetCenter(CGRect rect);
CGRect  CGRectMoveToCenter(CGRect rect, CGPoint center);

@interface UIView (MPMFrame)

@property CGPoint origin;
@property CGSize size;

@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;
@property (readonly) CGPoint topRight;

@property CGFloat x;
@property CGFloat y;
@property CGFloat height;
@property CGFloat width;

@property CGFloat top;
@property CGFloat left;

@property CGFloat bottom;
@property CGFloat right;

@property CGFloat centerX;
@property CGFloat centerY;

@end

NS_ASSUME_NONNULL_END
