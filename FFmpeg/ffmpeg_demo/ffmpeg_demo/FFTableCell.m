//
//  FFTableCell.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/1.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "FFTableCell.h"

@interface FFTableCell()

@property (nonatomic, strong) UILabel *textLab;

@end

@implementation FFTableCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        self.textLab = [UILabel new];
        self.textLab.frame = CGRectMake(0, 0, 200, 50);
        [self.contentView addSubview:self.textLab];
    }
    
    return self;
}

- (void)setTitle:(NSString *)title {
    _textLab.text = title;
}

@end
