//
//  Agent.h
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#ifndef __Simulation_Project__Agent__
#define __Simulation_Project__Agent__

#include <iostream>
#include <thread>
#include <ctime>
#include <mutex>

#include "Passenger.h"
#include "WaitingQueue.h"
#include "Config.h"

class Agent{
private:
    bool isCanadianAgent = 0;
    
public:
    Agent();
    Agent(bool);
    void SetIsCanadianAgent(bool);
    std::thread Processing(std::queue<Passenger *> *);
};

#endif /* defined(__Simulation_Project__Agent__) */
