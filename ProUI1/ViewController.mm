//
//  ViewController.m
//  ProUI1
//
//  Created by 吴子鸿 on 2017/3/14.
//  Copyright © 2017年 吴子鸿. All rights reserved.
//

#import "ViewController.h"


@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.bNum = 0;
    
    self.cellArray = [NSMutableArray arrayWithObjects:nil];
    
    self.isAmerican.state = 0;
    self.isAmerican.enabled = false;
    
    [self.baggageTable registerNib:[[NSNib alloc] initWithNibNamed:@"baggageMessage" bundle:nil] forIdentifier:@"cell"];

    // Do any additional setup after loading the view.
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}
- (IBAction)buggageChangeClick:(NSStepper *)sender {
    NSLog(@"当前行李个数：%d",self.bNum);
    if ([self.buggageChange intValue]>self.bNum)        //加了一个
    {
        self.bNum = (int)[self.buggageChange doubleValue];
        NSString *numString = [NSString stringWithFormat:@"%i", (int)[self.buggageChange doubleValue]];
        [self.buggageNum setStringValue:numString];
        [self.baggageTable beginUpdates];
        NSIndexSet* theIndexSet = [NSIndexSet indexSetWithIndex:[self.buggageChange integerValue]-1];
        [self.baggageTable insertRowsAtIndexes:theIndexSet withAnimation:NSTableViewAnimationEffectFade];
        [self.baggageTable endUpdates];
    }
    else if ([self.buggageChange intValue]<self.bNum)//减了一个
    {
        self.bNum = (int)[self.buggageChange doubleValue];
        NSString *numString = [NSString stringWithFormat:@"%i", (int)[self.buggageChange doubleValue]];
        [self.buggageNum setStringValue:numString];
        [self.baggageTable beginUpdates];
        NSIndexSet* theIndexSet = [NSIndexSet indexSetWithIndex:[self.buggageChange integerValue]];
        [self.baggageTable removeRowsAtIndexes:theIndexSet withAnimation:NSTableViewAnimationEffectFade];
        [self.baggageTable endUpdates];
        //[self.cellArray removeObjectAtIndex:[self.cellArray count]-1];  //数组里删除吧

    }
    else    //为0
    {
        //不动
    }
}

- (IBAction)calPriceButtonClick:(NSButton *)sender {
    int airLine = (int)[self.airLinePopUp indexOfSelectedItem];
    bool isAmerican = (bool)[self.isAmerican state];
    bool hasBaby = (bool)[self.hasBaby state];
    int position = (int)[self.positionPopUp indexOfSelectedItem];
    int price = (int)[self.price intValue];
    printf("%d\n%d\n%d\n%d\n%d\n",airLine,isAmerican,hasBaby,position,price);
    Baggage baggages[100];
    for (int i=0;i<[self.cellArray count];i++)
    {
        baggageMessage *cells = [self.cellArray objectAtIndex:i];
        Baggage baggage = Baggage(cells.weightText.doubleValue, cells.highText.doubleValue, cells.longText.doubleValue, cells.widthText.doubleValue);
        baggages[i] = baggage;
        NSLog(@"第%d个行李：%f %f %f %f",i,cells.weightText.doubleValue, cells.highText.doubleValue, cells.longText.doubleValue, cells.widthText.doubleValue);
    }
    if (price == 0)
    {
        [self ShowNSAlertWindow:-3];
        return;
    }
    CheckedBaggage checkedBaggage = CheckedBaggage();
    Traveler tra = Traveler(airLine, isAmerican, hasBaby, position, price, [self.cellArray count], baggages);
    double getPrice = checkedBaggage.checkIt(tra);
    if (getPrice < 0)
    {
        [self ShowNSAlertWindow:getPrice];
        return;
    }
    self.outPrice.stringValue = [NSString stringWithFormat:@"价格：%f",getPrice];
    
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    return 0;
}

- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row
{
    return 57;
}


#pragma mark table delegate
-(NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row{
    printf("+++1");
    if (row>=[self.cellArray count])
    {
        baggageMessage *cellView = [tableView makeViewWithIdentifier:@"cell" owner:self];
        cellView.baggageNum.stringValue = [NSString stringWithFormat:@"行李%d",(int)row+1];
        [self.cellArray addObject:cellView];
        return cellView;
    }
    baggageMessage *cellView = [tableView makeViewWithIdentifier:@"cell" owner:self];
    cellView.baggageNum.stringValue = [NSString stringWithFormat:@"行李%d",(int)row+1];
    [self.cellArray addObject:cellView];
    return cellView;
    
}
- (IBAction)airLineChanged:(id)sender { //选了国内航线就不能选择经过美国啦
    if ([self.airLinePopUp indexOfSelectedItem] == 0)
    {
        self.isAmerican.state = 0;
        self.isAmerican.enabled = false;
    }
    else
        self.isAmerican.enabled = true;
}

//禁止选中当前选择的行
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row{
    return 1;
}

//采用Modal Window的方式展示
- (void)ShowNSAlertWindow:(double)error
{
    
    NSAlert *alert = [NSAlert new];
    [alert addButtonWithTitle:@"确定"];
    [alert setMessageText:@"警告啊"];
    [alert setInformativeText:@"输入数据有误，请确认后重新输入"];
    [alert setAlertStyle:NSAlertStyleWarning];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if(returnCode == NSAlertFirstButtonReturn){
            NSLog(@"确定");
        }
    }];
    
}



@end
