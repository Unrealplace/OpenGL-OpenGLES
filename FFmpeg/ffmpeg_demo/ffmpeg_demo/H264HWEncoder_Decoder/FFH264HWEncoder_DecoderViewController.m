//
//  FFH264HWEncoder_DecoderViewController.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/3.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "FFH264HWEncoder_DecoderViewController.h"
#import <AVFoundation/AVFoundation.h>
#import "FFH264HWEncoder.h"
#import "FFH264HWDecoder.h"
#import "FFOpenGLRenderView.h"

@interface FFH264HWEncoder_DecoderViewController ()<AVCaptureVideoDataOutputSampleBufferDelegate,FFVideoEncoderDelegate,FFHWH264DecoderDelegate>

@property (nonatomic, strong) AVCaptureDeviceInput * captureDeviceInput;
@property (nonatomic, strong) AVCaptureVideoDataOutput *captureVideoDataOutput;
@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureConnection *captureConnection;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *videoPreviewLayer;

@property (nonatomic, assign) BOOL isCapturing;
@property (nonatomic, strong) FFH264HWEncoder *encoder;
@property (nonatomic, strong) FFH264HWDecoder *decoder;
@property (nonatomic, strong) FFOpenGLRenderView *playerView;

@end

@implementation FFH264HWEncoder_DecoderViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self initInput];
    
    UIButton *startBtn = [[UIButton alloc] initWithFrame:CGRectMake(0, 380, 50, 50)];
    startBtn.center = CGPointMake(self.view.frame.size.width / 2.f, startBtn.center.y);
    startBtn.backgroundColor = [UIColor redColor];
    [startBtn setTitle:@"开始" forState:UIControlStateNormal];
    [startBtn addTarget:self action:@selector(startCapture) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:startBtn];
    
    [self.view addSubview:self.playerView];
}

- (FFH264HWEncoder *)encoder {
    if (!_encoder) {
        FFVideoEncoderParam *param = [[FFVideoEncoderParam alloc] init];
        param.encodeWidth = 180;
        param.encodeHeight = 320;
        param.bitRate = 512 * 1024;
        param.maxKeyFrameInterVal = 10;
        _encoder = [[FFH264HWEncoder alloc] initWithParam:param];
        _encoder.delegate = self;
        [_encoder startVideoEncode];
    }
    
    return _encoder;
}

- (FFH264HWDecoder *)decoder {
    if (!_decoder) {
        _decoder = [[FFH264HWDecoder alloc] init];
        _decoder.delegate = self;
    }
    
    return _decoder;
}

- (FFOpenGLRenderView *)playerView {
    if (!_playerView) {
        _playerView = [[FFOpenGLRenderView alloc] initWithFrame:CGRectMake(self.view.frame.size.width / 2.f, 64, self.view.frame.size.width / 2.f - 10, 300)];
    }
    
    return _playerView;
}

// 初始化输入
- (void)initInput {
    NSArray *cameras = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    
    NSArray *captureDeviceArray = [cameras filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"position == %d",AVCaptureDevicePositionFront]];
    if (!captureDeviceArray.count) {
        NSLog(@"获取前置摄像头失败");
        return;
    }
    
    AVCaptureDevice *camera = captureDeviceArray.firstObject;
    NSError *errorMessage = nil;
    self.captureDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:camera error:&errorMessage];
    if (errorMessage) {
        NSLog(@"%@",errorMessage);
        return;
    }
    
    //    // 获取设置支持设置的帧率范围
    //    NSInteger frameRate = 15;
    //    AVFrameRateRange *frameRateRange = [self.captureDeviceInput.device.activeFormat.videoSupportedFrameRateRanges objectAtIndex:0];
    //    if (frameRate > frameRateRange.maxFrameRate || frameRate < frameRateRange.minFrameRate)
    //    {
    //        return;
    //    }
    //    // 设置输入的帧率
    //    self.captureDeviceInput.device.activeVideoMinFrameDuration = CMTimeMake(1, (int)frameRate);
    //    self.captureDeviceInput.device.activeVideoMaxFrameDuration = CMTimeMake(1, (int)frameRate);
    
    //初始化输出
    self.captureVideoDataOutput = [[AVCaptureVideoDataOutput alloc] init];
    NSDictionary *videoSetting = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarFullRange], kCVPixelBufferPixelFormatTypeKey, nil];
    [self.captureVideoDataOutput setVideoSettings:videoSetting];
    dispatch_queue_t outputQueue = dispatch_queue_create("acvideocaptureoutput_queue", DISPATCH_QUEUE_CONCURRENT);
    [self.captureVideoDataOutput setSampleBufferDelegate:self queue:outputQueue];
    self.captureVideoDataOutput.alwaysDiscardsLateVideoFrames = YES;
    
    //配置session
    self.captureSession = [[AVCaptureSession alloc] init];
    self.captureSession.usesApplicationAudioSession = NO;
    if ([self.captureSession canAddInput:self.captureDeviceInput]) {
        [self.captureSession addInput:self.captureDeviceInput];
    }
    if ([self.captureSession canAddOutput:self.captureVideoDataOutput]) {
        [self.captureSession addOutput:self.captureVideoDataOutput];
    }
    if ([self.captureSession canSetSessionPreset:AVCaptureSessionPreset640x480]) {
        self.captureSession.sessionPreset = AVCaptureSessionPreset640x480;
    }
    
    self.captureConnection = [self.captureVideoDataOutput connectionWithMediaType:AVMediaTypeVideo];
    self.captureConnection.videoOrientation = AVCaptureVideoOrientationPortrait;
    if (camera.position == AVCaptureDevicePositionFront && self.captureConnection.supportsVideoMirroring) {
        self.captureConnection.videoMirrored = YES;
    }
    
    
    // 获取预览Layer并设置视频方向，注意self.videoPreviewLayer.connection跟self.captureConnection不是同一个对象，要分开设置
    self.videoPreviewLayer = [AVCaptureVideoPreviewLayer layerWithSession:self.captureSession];
    self.videoPreviewLayer.connection.videoOrientation = self.captureConnection.videoOrientation;
    self.videoPreviewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    UIView * videoView = [[UIView alloc] initWithFrame:CGRectMake(10, 64, self.view.frame.size.width / 2.f - 10, 300)];
    [self.view addSubview:videoView];
    self.videoPreviewLayer.frame = videoView.bounds;
    [videoView.layer addSublayer:self.videoPreviewLayer];
}

- (BOOL)startCapture {
    if (self.isCapturing) {
        return NO;
    }
    
    AVAuthorizationStatus videoAuthStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if (videoAuthStatus != AVAuthorizationStatusAuthorized) {
        return NO;
    }
    
    [self.captureSession startRunning];
    self.isCapturing = YES;
    return YES;
}

- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    [self.encoder videoEncodeInputData:sampleBuffer forceKeyFrame:NO];
}

- (void)captureOutput:(AVCaptureOutput *)output didDropSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    
}

#pragma mark - H264 编码完成回掉
- (void)videoEncodeOutputDataCallback:(NSData *)data isKeyFrame:(BOOL)isKeyFrame {
    
    [self.decoder decodeNaluData:data];
}

- (void)videoDecoderOutputDataCallback:(CVImageBufferRef)imageBuffer {
    [self.playerView inputPixelBuffer:imageBuffer];
}

@end
