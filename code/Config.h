//
//  Config.h
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#ifndef __Simulation_Project__Config__
#define __Simulation_Project__Config__

#include <iostream>
#include <math.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <mutex>

#include "Passenger.h"

const static int passengerNum = 700;
const static int cPassNum = 455;
const static int vPassNum = 245;
const static int arr_interval = 20*60*1000/(passengerNum-1);
const static int agentNum = 16;
static int numOfCanadianAgent = 13;
const static int numOfVisitorAgent = agentNum - numOfCanadianAgent;
static bool isStrategyOne = false;

static std::mutex locker;

int * GenExpDist(int, double);
bool GeneratePassenger(Passenger *);

#endif /* defined(__Simulation_Project__Config__) */

