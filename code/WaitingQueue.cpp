//
//  WaitingQueue.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include "WaitingQueue.h"
WaitingQueue::WaitingQueue()
{
    if (isStrategyOne)
    {
        /*create 2 queues, one for Canadian, one for visitor*/
        customQueue = new std::queue<Passenger *>[2];
    }
    else
    {
        /*create 16 queues, one for each agent*/
        customQueue = new std::queue<Passenger *>[agentNum];
    }
    
}

WaitingQueue::~WaitingQueue()
{
    delete[] customQueue;
}

std::queue<Passenger *>* WaitingQueue::GetQueue(int queueNum)
{
    std::queue<Passenger *> *p = NULL;
    if (isStrategyOne)
    {
        if ((queueNum < 2) && (queueNum >=0))
        {
            p = &(customQueue[queueNum]);
        }
    }
    else
    {
        if ((queueNum < agentNum) && (queueNum >=0))
        {
            p = &(customQueue[queueNum]);
        }
    }
    
    return p;
}

/*If this is strategy one, Canadian joins the Canadian queue, visitor joins the visitor queue*/
void JoinQueueQne(Passenger *passenger, WaitingQueue * wq)
{
    Passenger *p = NULL;
    time_t startTime;
    
    for (int i = 0; i< passengerNum; i++)
    {
        p = &passenger[i];
        
        if (true == p->GetIsCanadian())
        {
            wq->GetQueue(0)->push(p);
        }
        else
        {
            wq->GetQueue(1)->push(p);
        }
        startTime = time(0);
        passenger[i].SetStartTime(startTime);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(arr_interval));
    }
}

/*If this is strategy two, Canadian joins the shortest Canadian queue, visitor joins the shortest visitor queue*/
void JoinQueueTwo(Passenger *passenger, WaitingQueue * wq)
{
    Passenger *p = NULL;
    std::queue<Passenger *> *q = NULL;
    time_t startTime;
    
    for (int i = 0; i< passengerNum; i++)
    {
//        locker.lock();
        p = &passenger[i];
        if (p->GetIsCanadian())
        {
            q = wq->GetQueue(0);
            for (int j = 1; j< numOfCanadianAgent; j++)
            {
                if ((q->size()) > (wq->GetQueue(j)->size()))
                {
                    q = wq->GetQueue(j);
                }
            }
            q->push(p);
        }
        else
        {
            q = wq->GetQueue(numOfCanadianAgent + 0);
            for (int j = numOfCanadianAgent + 1; j< agentNum; j++)
            {
                if ((q->size()) > (wq->GetQueue(j)->size()))
                {
                    q = wq->GetQueue(j);
                }
            }
            q->push(p);
        }
        startTime = time(0);
        passenger[i].SetStartTime(startTime);
//        locker.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(arr_interval));
    }
}

/*This function is for adding passengers into queues, different strategies has different algorithm*/
void WaitingQueue::AddIntoQueue(Passenger *passenger)
{
    if (isStrategyOne)
    {
        JoinQueueQne(passenger, this);
    }
    else
    {
        JoinQueueTwo(passenger, this);
    }
}
