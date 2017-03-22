//
//  ViewController.h
//  ProUI1
//
//  Created by 吴子鸿 on 2017/3/14.
//  Copyright © 2017年 吴子鸿. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CheckedBaggage.h"
#import "baggageMessage.h"

@interface ViewController : NSViewController <NSTableViewDelegate,NSTableViewDataSource>
@property (weak) IBOutlet NSPopUpButton *airLinePopUp;
@property (weak) IBOutlet NSButton *isAmerican;
@property (weak) IBOutlet NSButton *hasBaby;
@property (weak) IBOutlet NSPopUpButton *positionPopUp;
@property (weak) IBOutlet NSTextField *price;
@property (weak) IBOutlet NSTextField *buggageNum;
@property (weak) IBOutlet NSStepper *buggageChange;
@property (weak) IBOutlet NSTextField *outPrice;
@property int bNum;
@property (weak) IBOutlet NSTableView *baggageTable;
@property NSMutableArray *cellArray;


@end

