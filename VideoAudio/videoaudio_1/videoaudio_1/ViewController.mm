//
//  ViewController.m
//  videoaudio_1
//
//  Created by mpm on 2020/7/29.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "ViewController.h"
#include "Mp3Encoder.hpp"
#import "CommonUtil.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIButton *startBtn = [[UIButton alloc] initWithFrame:CGRectMake(100, 100, 90, 60)];
    [self.view addSubview:startBtn];
    [startBtn setTitle:@"开始编码" forState:UIControlStateNormal];
    startBtn.backgroundColor = [UIColor orangeColor];
    [startBtn addTarget:self action:@selector(startBtnClick) forControlEvents:UIControlEventTouchUpInside];
    
}

- (void)startBtnClick {
    NSLog(@"Start Encode...");
    const char * pcmFilePath = [[CommonUtil bundlePath:@"vocal.pcm"] cStringUsingEncoding:NSUTF8StringEncoding];
    const char * mp3FilePath = [[CommonUtil documentsPath:@"vocal.mp3"] cStringUsingEncoding:NSUTF8StringEncoding];
    int sampleRate = 44100;
    int channels = 2;
    int bitRate = 128 * 1024;
    Mp3Encoder * encoder = new Mp3Encoder();
    encoder->Init(pcmFilePath, mp3FilePath, sampleRate, channels, bitRate);
    encoder->Encode();
    encoder->Destory();
    delete encoder;
    NSLog(@"Encode Success");
}

@end
