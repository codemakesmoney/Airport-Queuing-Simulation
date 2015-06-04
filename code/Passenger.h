//
//  Passenger.h
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#ifndef __Simulation_Project__Passenger__
#define __Simulation_Project__Passenger__

#include <iostream>
#include <ctime>
class Passenger{
private:
    time_t startTime = 0;
    time_t endTime = 0;
    int serviceTime = 0;
    bool isCanadian = 0;
    /*these two marks has no real meaning, just for disordering the passengers*/
    int mark0 = 0;
    int mark1 = 0;
    
public:
    Passenger();
    ~Passenger();
    time_t GetStartTime();
    
    void SetStartTime(time_t _startTime);
    
    time_t GetEndTime();
    
    void SetEndTime(time_t _endTime);
    
    bool GetIsCanadian();
    
    void SetIsCanadian(bool _isCanadian);
    
    int GetServiceTime();
    
    void SetServiceTime(int _serviceTime);
    
    int GetMark0();
    
    void SetMark0(int);
    
    int GetMark1();
    
    void SetMark1(int _mark);
    
    
};

#endif /* defined(__Simulation_Project__Passenger__) */
