//
//  CheckedBaggage.cpp
//  Pro1
//
//  Created by 吴子鸿 on 2017/3/9.
//  Copyright © 2017年 吴子鸿. All rights reserved.
//

#include "CheckedBaggage.h"



//国内航线计算
double CheckedBaggage::calLineZero(Traveler traveler)
{
    if (traveler.position == 0) //头等舱                   //*1
    {
        return nationPrice(40, traveler);
    }
    else if (traveler.position == 1)   //公务舱            //*1
    {
        return nationPrice(30, traveler);
    }
    else if (traveler.position == 3)    //经济舱           //*1
    {
        return nationPrice(20, traveler);
    }
    else
        return -2;
    
}

//计算国内行李价格
//参数:
//weight:旅客行李最大重量
double CheckedBaggage::nationPrice(double weight,Traveler traveler)
{
    if ((traveler.baggageNum == 0) || (traveler.baggageNum == 1 && traveler.baggage[0].weight<=weight))
        return 0;   //不花钱           //*1
    else    //要花钱
    {
        int babyBagNum = -1;    //婴儿行李的编号，-1代表没有
        //有婴儿并且婴儿行李重量小于10kg，免费，默认不用计算
        if (traveler.hasBaby && traveler.baggage[traveler.baggageNum].weight <= 10)     //*1
            for (int i = traveler.baggageNum-1;i>=0;i--)
                if (traveler.baggage[i].weight<=10)                                     //*1
                    babyBagNum = i;
        //无论是一件行李还是多件行李都这么算！
        int arr=0;    //行李除过最大没超重的总重量
        int maxk=0; //最大没超重的重量
        for (int i=0;i<traveler.baggageNum;i++)  //找出没超重的最大的，其他算超重
        {
            if (i == babyBagNum)    //婴儿行李不用算       //*1
                continue;
            if (traveler.baggage[i].weight<=weight && traveler.baggage[i].weight>maxk)      //*1
                maxk = traveler.baggage[i].weight;
            arr = arr+traveler.baggage[i].weight;
        }
        if (maxk == 0)                          //*1
            maxk = weight;
        arr = arr-maxk;
        return arr*traveler.ticketPrice*0.015;
    }
}

//区域一
double CheckedBaggage::calLineOne(Traveler traveler)
{
    if (traveler.position == 0) //头等舱       //*1
    {
        if (isOver(3, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 32, 158, 1000, 2000, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 1) //公务舱      //*1
    {
        if (isOver(2, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 32, 158, 1000, 2000, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 2 || traveler.position == 3)  //明珠经济舱／经济舱     //*1
    {
        if (isOver(2, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 23, 158, 1000, 2000, 1000, 32, 1000, 3000, traveler);
    }
    return -2;  //输入数据错误
}

//区域二
double CheckedBaggage::calLineTwo(Traveler traveler)
{
    if (traveler.position == 0) //头等舱           //*1
    {
        if (isOver(3, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 32, 158, 450, 1300, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 1) //公务舱          //*1
    {
        if (isOver(2, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 32, 158, 450, 1300, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 2 || traveler.position == 3)  //明珠经济舱／经济舱     //*1
    {
        if (isOver(1, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(1, 32, 158, 450, 1300, 1000, 45, 3000, 3000, traveler);
    }
    return -2;
}

//区域三
double CheckedBaggage::calLineThree(Traveler traveler)
{
    if (traveler.position == 0) //头等舱
    {
        if (isOver(3, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 32, 158, 1000, 2000, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 1) //公务舱
    {
        if (isOver(2, 32, 158, traveler) == false)
            return 0;
        else
            return  overPrice(2, 32, 158, 1000, 2000, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 2 || traveler.position == 3)  //明珠经济舱／经济舱
    {
        if (isOver(2, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 23, 158, 1000, 2000, 1000, 32, 2000, 3000, traveler);
    }
    return -2;
}

//区域四
double CheckedBaggage::calLineFour(Traveler traveler)
{
    if (traveler.position == 0) //头等舱
    {
        if (isOver(3, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 32, 158, 450, 1300, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 1) //公务舱
    {
        if (isOver(3, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 23, 158, 450, 1300, 1000, 32, 1000, 3000, traveler);
    }
    else if (traveler.position == 2)  //明珠经济舱
    {
        if (isOver(2, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 23, 158, 450, 1300, 1000, 32, 1000, 3000, traveler);
    }
    else if (traveler.position == 3)    //经济舱
    {
        if (isOver(1, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(1, 23, 158, 450, 1300, 1000, 32, 1000, 3000, traveler);
    }
    return -2;
}

//涉及韩国始发与中国间的航程
double CheckedBaggage::calLineFive(Traveler traveler)
{
    if (traveler.position == 0) //头等舱
    {
        if (isOver(3, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(3, 32, 158, 450, 1300, 1000, 45, 3000, 3000, traveler);
    }
    else if (traveler.position == 1) //公务舱
    {
        if (isOver(2, 32, 158, traveler) == false)
            return 0;
        else
            return overPrice(2, 32, 158, 450, 1300, 1000, 32, 1000, 3000, traveler);
    }
    else if (traveler.position == 2)  //明珠经济舱，不存在，所以-2
    {
        return -2;
    }
    else if (traveler.position == 3)
    {
        if (isOver(1, 23, 158, traveler) == false)
            return 0;
        else
            return overPrice(1, 23, 158, 450, 1300, 1000, 32, 1000, 3000, traveler);
    }
    return -2;
}


//判断是否是免费行李
//参数：
//num:行李最大数量
//weight:每件行李重量上限
//size:每件行李最大尺寸
//traveler  //旅客属性
//返回值：false：未超重。  true：超重。
bool CheckedBaggage::isOver(int num,double weight,double size,Traveler traveler)
{
    if (traveler.baggageNum == 0)   //没行李，不超重               //*1
        return false;
    else
    {
        if (traveler.baggageNum<=num && traveler.baggage[0].weight<=weight)   //行李数量、最大重量均小于最小限制                //*1
        {
            //看尺寸
            for (int i=0;i<traveler.baggageNum;i++)
                if (traveler.baggage[i].size<size)              //*1
                    return true;    //超尺寸超限了
            return false;
        }
        if (traveler.hasBaby && traveler.baggageNum == num+1 && traveler.baggage[0].weight<=weight && traveler.baggage[traveler.baggageNum-1].weight <= 10)    //有婴儿多带一件也不超     //*1
        {
            bool babyBag = false;
            for (int i=traveler.baggageNum-1;i<0;i--)
            {
                if (traveler.baggage[i].size<size)          //*1
                    return true;    //超尺寸超限了
                if (traveler.baggage[i].size<115 && traveler.baggage[i].weight<=10)     //*1
                    babyBag = true; //有一件认为是婴儿行李
            }
            if (babyBag)
                return false;
            return true;
        }
        return true;    //超限了
    }
}

//计算超额行李价格
//参数:
//freeCount:免费行李个数
//maxFreeWeight:最大免费重量
//maxFreeSize:最大免费尺寸(均为158)
//overOneBaggagePrice:超件（第一件）收费标准  元/件
//overTwoBaggagePrice:超件（第二件或更多）收费标准  元/件
//overSizePrice:超尺寸收费标准  元
//overWeight1:第一个超重的最大重量
//overWeight1Price:第一个超重要收费的费用
//overWeight2:第二个超重的大重量
//overWeight2Price:第二个超重要收费的费用
//traveler:旅客信息
double CheckedBaggage::overPrice(int freeCount,double maxFreeWeight,double maxFreeSize,double overOneBaggagePrice,double overTwoBaggagePrice,double overSizePrice,double overWeight1,double overWeight1Price,double overWeight2Price,Traveler traveler)
{
    double price = 0;
    int babyBag = -1;
    int exceptBabyBagNum = traveler.baggageNum; //除过婴儿行李，有的行李件数
    //寻找婴儿满足的行李
    if (traveler.hasBaby)       //*1
        for (int i=0;i<traveler.baggageNum;i++)
            if (traveler.baggage[i].size<=115 && traveler.baggage[i].weight<=10)        //*1
            {
                babyBag = i;
                exceptBabyBagNum--;
                break;
            }
    //是否超件，超件的话计算超件的行李费用
    if (exceptBabyBagNum>freeCount)             //*1
    {
        if (exceptBabyBagNum == freeCount+1) //超了一件行李               //*1
            price = price+overOneBaggagePrice;
        else        //超了多件行李
            price = price+overOneBaggagePrice+(exceptBabyBagNum-freeCount-1)*overTwoBaggagePrice;
    }
    //超重、超尺寸行李价格计算
    for (int i=0;i<traveler.baggageNum;i++)
    {
        Baggage baggage = traveler.baggage[i];
        if (baggage.size>maxFreeSize)   //检查尺寸              //*1
            price = price+overSizePrice;
        if (baggage.weight>maxFreeWeight)                   //*1
        {
            //检查重量
            if (baggage.weight<=overWeight1)                //*1
                price = price+overWeight1Price;
            else
                price = price+overWeight2Price;
        }
    }
    return price;
}
