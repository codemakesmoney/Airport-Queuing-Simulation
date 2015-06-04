//
//  Agents.h
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#ifndef __Simulation_Project__Agents__
#define __Simulation_Project__Agents__

#include <iostream>
#include <thread>
#include "Agent.h"
#include "WaitingQueue.h"
#include "Config.h"
class Agents{
private:
    Agent *agents;
    
    
public:
    Agents();
    ~Agents();
    
    void Processing(WaitingQueue*, std::thread *);
};
#endif /* defined(__Simulation_Project__Agents__) */
