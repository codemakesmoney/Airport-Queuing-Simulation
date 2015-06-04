//
//  WaitingQueue.h
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#ifndef __Simulation_Project__WaitingQueue__
#define __Simulation_Project__WaitingQueue__

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include "Passenger.h"
#include "Config.h"


class WaitingQueue{
    private :
    std::queue<Passenger *> *customQueue;
    
public:
    WaitingQueue();
    ~WaitingQueue();
    
    void AddIntoQueue(Passenger *);
    std::queue<Passenger *>* GetQueue(int);
    
};
#endif /* defined(__Simulation_Project__WaitingQueue__) */
