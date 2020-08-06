//
//  UICollectionView+MPMAdd.m
//  MPMCategory_Example
//
//  Created by Done.L on 2019/6/27.
//  Copyright © 2019 823890952@qq.com. All rights reserved.
//

#import "UICollectionView+MPMAdd.h"

@implementation UICollectionView (MPMAdd)

+ (UICollectionView *)cm_collectionViewWithSuperView:(UIView *)superView delegate:(id)delegate layout:(UICollectionViewLayout *)layout constraint:(void (^)(MASConstraintMaker *))constraint configureHandler:(void (^)(UICollectionView *, UICollectionViewFlowLayout *))configureHandler {
    if (layout == nil) {
        layout = [self defaultFlowLayoutWithScrollDirection:UICollectionViewScrollDirectionVertical];
    }
    
    UICollectionView *view = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:layout];
    view.delegate = delegate;
    view.dataSource = delegate;
    view.backgroundColor = [UIColor whiteColor];
    
    [superView addSubview:view];
    [view mas_makeConstraints:constraint];
    if (configureHandler) {
        configureHandler(view, layout);
    }
    
    return view;
}

+ (UICollectionViewFlowLayout *)defaultFlowLayoutWithScrollDirection:(UICollectionViewScrollDirection)scrollDirection {
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    [layout setScrollDirection:scrollDirection];
    return layout;
}

@end
