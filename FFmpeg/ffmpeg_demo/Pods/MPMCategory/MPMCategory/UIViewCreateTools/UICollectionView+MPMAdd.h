//
//  UICollectionView+MPMAdd.h
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "Masonry.h"

NS_ASSUME_NONNULL_BEGIN

@interface UICollectionView (MPMAdd)

+ (UICollectionView *)cm_collectionViewWithSuperView:(UIView *)superView delegate:(id)delegate layout:(UICollectionViewLayout *)layout constraint:(void (^)(MASConstraintMaker *make))constraint configureHandler:(void (^)(UICollectionView *view, UICollectionViewFlowLayout *layout))configureHandler;

+ (UICollectionViewFlowLayout *)defaultFlowLayoutWithScrollDirection:(UICollectionViewScrollDirection)scrollDirection;

@end

NS_ASSUME_NONNULL_END
