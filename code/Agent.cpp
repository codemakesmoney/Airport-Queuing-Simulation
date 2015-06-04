//
//  Agent.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include "Agent.h"

std::mutex mtxCanadian;
std::mutex mtxVisitor;
int pasCanProcessed = 0;
int pasVisProcessed = 0;
int pasProcessed = 0;

Agent::Agent(bool _isCanadianAgent){
    isCanadianAgent = _isCanadianAgent;
}

Agent::Agent(){
    isCanadianAgent = 0;
}

void Agent::SetIsCanadianAgent(bool _isCanadianAgent)
{
    isCanadianAgent = _isCanadianAgent;
}

void CanadianProcess(std::queue<Passenger *> *canadianQueue)
{
    time_t endTime = 0;
    Passenger * p = NULL;
    
    /*If there is still passengers to be processed*/
    while (pasCanProcessed<cPassNum)
    {
        mtxCanadian.lock();
        /*If the queue is not empty*/
        if (!canadianQueue->empty())
        {
            /*Get the first passenger from the queue*/
            pasCanProcessed += 1;
            p=canadianQueue->front();
            canadianQueue->pop();
            //std::cout<<"Canadian "<<pasCanProcessed<<" is being processed."<<std::endl;
        }
        mtxCanadian.unlock();
        /*process for some time*/
        if (p != NULL) {
            std::this_thread::sleep_for(std::chrono::milliseconds(p->GetServiceTime()));
            endTime = time(0);
            p->SetEndTime(endTime);
            p = NULL;
        }
    }
}

/*similar as the function above*/
void VisitorProcess(std::queue<Passenger *> *visitorQueue)
{
    time_t endTime = 0;
    Passenger * p = NULL;
    
    while ( pasVisProcessed < vPassNum )
    {
        mtxVisitor.lock();
        if (!visitorQueue->empty())
        {
            pasVisProcessed += 1;
            p = visitorQueue->front();
            visitorQueue->pop();
            //std::cout<<"Visitor "<<pasVisProcessed<<" is being processed"<<std::endl;
        }
        mtxVisitor.unlock();
        if (p != NULL)
        {
            std::this_thread::sleep_for( std::chrono::milliseconds(p->GetServiceTime()));
            endTime = time(0);
            p->SetEndTime(endTime);
            p = NULL;
        }
    }
}

/*This function is for strategy two, where each agent has its own queue, so we do not need to lock the queues*/
void ProcessFunction(std::queue<Passenger *> *q)
{
    time_t endTime = 0;
    Passenger * p = NULL;
    
   while ( pasProcessed < passengerNum )
    {
//        locker.lock();
        if (!q->empty())
        {
            locker.lock();
            pasProcessed += 1;
            locker.unlock();
            p = q->front();
            q->pop();
        }
//        locker.unlock();
        if (p != NULL)
        {
            std::this_thread::sleep_for( std::chrono::milliseconds(p->GetServiceTime()));
            endTime = time(0);
            p->SetEndTime(endTime);
            p = NULL;
        }
    }
}

std::thread Agent::Processing(std::queue<Passenger *> *q)
{
    std::thread t;
    if (isStrategyOne)
    {
        if(isCanadianAgent)
        {
            t = std::thread(CanadianProcess, q);
        }
        else
        {
            t = std::thread(VisitorProcess, q);
        }
    }
    else
    {
        t = std::thread(ProcessFunction, q);
    }
    return t;
    
}


