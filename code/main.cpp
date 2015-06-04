//
//  main.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include <iostream>

#include <time.h>
#include <thread>
#include <ctime>
#include "Passenger.h"
#include "WaitingQueue.h"
#include "Config.h"
#include "Agents.h"


void Analysis(Passenger * passenger)
{
    double totalTime = 0;
    double averageTIme = 0;
    time_t start = 0;
    time_t end = 0;
    struct tm * startInfo;
    struct tm * endInfo;
    
    /*sum up the time each passenger spend in this area*/
    for (int i = 0; i < passengerNum; i++)
    {
        start = passenger[i].GetStartTime();
        end = passenger[i].GetEndTime();
        totalTime = totalTime + difftime(end, start);
        
        startInfo = localtime ( &start);
        endInfo = localtime ( &end);
        std::cout<<"Passenger "<<i+1<<" interval is "<<difftime(end,start)<<" sec"<<std::endl;
    }
    
    /*calculate the average waiting + processing time*/
    averageTIme = totalTime / passengerNum;
    std::cout<<"average time is "<<averageTIme<<" sec"<<std::endl;
}

void Queueing(WaitingQueue *wq, Passenger * p)
{
    wq->AddIntoQueue(p);
}


int main(int argc, const char * argv[])
{
    /*Ask for user's options: strategy be used and number of Canadian agents.*/
    char _isStratety;
    int _canadianAgentNum = 0;
    std::cout<<"Is this strategy one? (y/n)"<<std::endl;
    std::cin>>_isStratety;
    if (_isStratety == 'y') {
        isStrategyOne = true;
    }else if(_isStratety == 'n'){
        isStrategyOne = false;
    }else{
        std::cout<<"Wrong input"<<std::endl;
        return 0;
    }
    
    std::cout<<"How many Canadian agents do you want?(0~16)"<<std::endl;
    std::cin>>_canadianAgentNum;
    if ((0 <= _canadianAgentNum) &&(16 >=_canadianAgentNum))  {
        numOfCanadianAgent = _canadianAgentNum;
    }else{
        std::cout<<"Wrong input"<<std::endl;
        return 0;
    }
    
    std::cout<<"Start processing. It will take a long time, maybe one or two hours, please wait patiently."<<std::endl;
    /*Create threads, one for passengers join the queue, 16 for each agents.*/
     std::thread tQueue;
     std::thread tAgent[agentNum];
    
    /*700 passenger*/
     Passenger *passenger = new Passenger[passengerNum];
    
    /*Decide each passenger's service time and whether he is a Canadian */
     GeneratePassenger(passenger);
    
    /*Generate waiting queues, passengers start to join the queues.*/
     WaitingQueue *wq = new WaitingQueue();
     tQueue = std::thread(Queueing, wq, passenger);
    
    /*Generate agents, and start processing*/
     Agents *agents = new Agents();
     agents->Processing(wq, tAgent);
    
     tQueue.join();
     for (int i = 0; i < agentNum; i++)
     {
     tAgent[i].join();
     }
    
    /*Count the average waiting + processing time*/
     Analysis(passenger);
     
     delete [] passenger;
     delete wq;
     delete agents;
    
    return 0;
}



