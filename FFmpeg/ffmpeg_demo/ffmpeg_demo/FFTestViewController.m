//
//  FFTestViewController.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/1.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "FFTestViewController.h"

#include "avformat.h"
#include "swscale.h"
#include "swresample.h"
#include "pixdesc.h"

@interface FFTestViewController ()

@end

@implementation FFTestViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    
    avcodec_register_all();
}


@end
