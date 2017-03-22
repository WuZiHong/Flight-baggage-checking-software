//
//  baggageMessage.h
//  ProUI1
//
//  Created by 吴子鸿 on 2017/3/14.
//  Copyright © 2017年 吴子鸿. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface baggageMessage : NSTableCellView
@property (weak) IBOutlet NSTextField *weightText;
@property (weak) IBOutlet NSTextField *highText;
@property (weak) IBOutlet NSTextField *longText;
@property (weak) IBOutlet NSTextField *widthText;
@property (weak) IBOutlet NSTextField *baggageNum;

@end
