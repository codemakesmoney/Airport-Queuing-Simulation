//
//  Passenger.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include "Passenger.h"
Passenger::Passenger()
{
    startTime = 0;
    endTime = 0;
    isCanadian = 0;
    serviceTime = 0;
    mark0 = 0;
    mark1 = 0;
}

Passenger::~Passenger()
{
    
}

time_t Passenger::GetStartTime()
{
    return startTime;
}

void Passenger::SetStartTime(time_t _startTime)
{
    startTime = _startTime;
}

time_t Passenger::GetEndTime()
{
    return endTime;
}

void Passenger::SetEndTime(time_t _endTime)
{
    endTime = _endTime;
}

bool Passenger::GetIsCanadian()
{
    return isCanadian;
}

void Passenger::SetIsCanadian(bool _isCanadian)
{
    isCanadian= _isCanadian;
}

int Passenger::GetServiceTime()
{
    return serviceTime;
}

void Passenger::SetServiceTime(int _serviceTime)
{
    serviceTime = _serviceTime;
}

int Passenger::GetMark0()
{
    return mark0;
}

void Passenger::SetMark0(int _mark)
{
    mark0 = _mark;
}

int Passenger::GetMark1()
{
    return mark1;
}

void Passenger::SetMark1(int _mark)
{
    mark1 = _mark;
}