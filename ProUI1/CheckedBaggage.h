//
//  CheckedBaggage.hpp
//  Pro1
//
//  Created by 吴子鸿 on 2017/3/9.
//  Copyright © 2017年 吴子鸿. All rights reserved.
//

#ifndef CheckedBaggage_hpp
#define CheckedBaggage_hpp

#include <stdio.h>

struct Baggage {    //行李
    double weight;  //行李重量  单位：千克
    double x,y,z;   //行李的三维 x:高。y：正面的长。z：侧面的宽   单位：cm
    double size;
    Baggage(double w,double a,double b,double c)
    {
        weight = w;
        x=a;
        y=b;
        z=c;
        size = a+b+c;
    }
    Baggage()
    {
        weight = x = y = z = size = 0;
    }
};

struct Traveler {   //旅客
    int airLine;    //航线    0:国内。   x：代表区域x的航线
    bool isInAmerican;    //涉及美国航线
    bool hasBaby;    //是否有婴儿
    int position;   //仓位    0:头等舱   1:公务舱   2:明珠经济舱   3:经济舱
    double ticketPrice;      //票价
    
    int baggageNum;    //行李个数
    Baggage baggage[100];
    
    
    Traveler(int AirLine,bool IsInAmerican,bool HasBaby,int Position,double TicketPrice,int BaggageNum,Baggage Bag[])
    {
        airLine = AirLine;
        isInAmerican = IsInAmerican;
        hasBaby = HasBaby;
        position = Position;
        ticketPrice = TicketPrice;
        baggageNum = BaggageNum;
        for (int i=0;i<baggageNum;i++)
            baggage[i] = Bag[i];
        sortBaggage(0, baggageNum-1);
    }
    
    void sortBaggage(int l,int r)   //对快递按照重量排序
    {
        if (l == r)
            return;
        int x=l,y=r;
        double m = baggage[(l+r)/2].weight;
        do
        {
            while (baggage[x].weight>m) x++;
            while (baggage[y].weight<m) y--;
            if (x<=y)
            {
                Baggage k;
                k=baggage[x];
                baggage[x]=baggage[y];
                baggage[y]=k;
                x++;
                y--;
            }
        }while(x<=y);
        if (l<y) sortBaggage(l, y);
        if (x<r) sortBaggage(x, r);
    }
};


class CheckedBaggage {  //行李托运判断函数
    
    
public:
    
    double checkIt(Traveler traveler)    //-1代表不满足，不让运送行李
    {
        //判断是否满足最高条件，不满足返回-1
        if (traveler.baggageNum<0 || traveler.baggageNum>10)
            return -1;
        if (traveler.airLine == 0)  //是国内航班                             //*1
        {
            for (int i=0;i<traveler.baggageNum;i++)
            {
                Baggage baggage = traveler.baggage[i];
                if (baggage.weight>50 || baggage.weight<=0)                                      //*1
                    return -1;
                if (baggage.x>100 || baggage.x<1 || baggage.y>60 || baggage.y<1 || baggage.z>40 || baggage.z<1)          //*1
                    return -1;
            }
        }
        else
        {
            if (traveler.isInAmerican)  //涉及美国航线                        //*1
            {
                for (int i=0;i<traveler.baggageNum;i++)
                {
                    Baggage baggage = traveler.baggage[i];
                    if (baggage.x<1 || baggage.y<1 || baggage.z<1)
                        return -1;
                    if (baggage.weight>45 || baggage.weight<0)                                  //*1
                        return -1;
                    if (baggage.size>300 || baggage.size <0)                                   //*1
                        return -1;
                }
            }
            else
            {
                for (int i=0;i<traveler.baggageNum;i++)
                {
                    Baggage baggage = traveler.baggage[i];
                    if (baggage.x<1 || baggage.y<1 || baggage.z<1)
                        return -1;
                    if (baggage.weight>32 || baggage.weight<0)                                  //*
                        return -1;
                    if (baggage.size>300 || baggage.size<0)                                   //*
                        return -1;
                }
            }
        }
        //满足最大限度，开始计算价格
        if (traveler.airLine == 0)  //0代表国内航班的航线，算国内的价格         //*1
        {
            return calLineZero(traveler);
        }
        else if (traveler.airLine == 1)     //1代表区域一                    //*
        {
            return calLineOne(traveler);
        }
        else if (traveler.airLine == 2)     //2代表区域二                    //*
        {
            return calLineTwo(traveler);
        }
        else if (traveler.airLine == 3)     //3代表区域三                    //*
        {
            return calLineThree(traveler);
        }
        else if (traveler.airLine == 4)     //4代表区域四                    //*
        {
            return calLineFour(traveler);
        }
        else if (traveler.airLine == 5)     //涉及韩国始发与中国间的航程         //*
        {
            return calLineFive(traveler);
        }
        else
            return -1;  //不存在的航线
    }
    
//private:
    double calLineZero(Traveler traveler);  //国内航线计算
    double calLineOne(Traveler traveler);  //区域一
    double calLineTwo(Traveler traveler);  //区域二
    double calLineThree(Traveler traveler);  //区域三
    double calLineFour(Traveler traveler);  //区域四
    double calLineFive(Traveler traveler);  //涉及韩国始发与中国间的航程
    
    //判断是否是免费行李
    //参数：
    //num:行李最大数量
    //weight:每件行李重量上限
    //size:每件行李最大尺寸
    bool isOver(int num,double weight,double size,Traveler traveler);
    
    //计算国内行李价格
    //参数:
    //weight:旅客行李最大重量
    double nationPrice(double weight,Traveler traveler);
    
    //计算超额行李价格
    //参数:
    //freeCount:免费行李个数
    //maxFreeWeight:最大免费重量
    //maxFreeSize:最大免费尺寸(均为158)
    //overOneBaggage:超件（第一件）收费标准  元/件
    //overTwoBaggage:超件（第二件或更多）收费标准  元/件
    //overSize:超尺寸收费标准  元
    //overWeight1:第一个超重的最小重量
    //overWeight1Price:第一个超重要收费的费用
    //overWeight2:第二个超重的小重量
    //overWeight2Price:第二个超重要收费的费用
    //traveler:旅客信息
    double overPrice(int freeCount,double maxFreeWeight,double maxFreeSize,double overOneBaggagePrice,double overTwoBaggagePrice,double overSizePrice,double overWeight1,double overWeight1Price,double overWeight2Price,Traveler traveler);
    
};

#endif /* CheckedBaggage_hpp */
