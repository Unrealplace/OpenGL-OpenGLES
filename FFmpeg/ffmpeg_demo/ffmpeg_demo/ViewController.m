//
//  ViewController.m
//  ffmpeg_demo
//
//  Created by mpm on 2020/8/1.
//  Copyright © 2020 mpm. All rights reserved.
//

#import "ViewController.h"
#import "FFBaseViewController.h"

#import "FFTableCell.h"
#import "FFTableModel.h"

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>

@property (nonatomic, strong) UITableView *tableview;
@property (nonatomic, strong) NSMutableArray *dataSource;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view addSubview:self.tableview];
    
    self.dataSource = [NSMutableArray array];
    
    NSArray *title = @[@"使用VideoToolBox硬编解码h264文件"];
    NSArray *titleClass = @[@"FFH264HWEncoder_DecoderViewController"];
    
    for (NSInteger i = 0; i < titleClass.count; i++) {
        FFTableModel *model = [[FFTableModel alloc] init];
        model.title = title[i];
        model.vcClass = titleClass[i];
        [self.dataSource addObject:model];
    }

}

- (UITableView *)tableview {
    if (!_tableview) {
        _tableview = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) style:UITableViewStyleGrouped];
        _tableview.delegate = self;
        _tableview.dataSource = self;
        [_tableview registerClass:[FFTableCell class] forCellReuseIdentifier:@"FFTableCell"];
    }
    
    return _tableview;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataSource.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    FFTableCell * cell = [tableView dequeueReusableCellWithIdentifier:@"FFTableCell"];
    if (!cell) {
        cell = [[FFTableCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"FFTableCell"];
    }
    
    FFTableModel * model = self.dataSource[indexPath.row];
    cell.title = model.title;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    FFTableModel *model = self.dataSource[indexPath.row];
    FFBaseViewController *vc = [NSClassFromString(model.vcClass) new];
    
    [self.navigationController pushViewController:vc animated:YES];
}
@end
