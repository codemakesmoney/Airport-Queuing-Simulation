//
//  Agents.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-13.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include "Agents.h"
Agents::Agents()
{
    agents = new Agent[agentNum];
    
    /*create numOfCanadianAgent agents and (16 - numOfCanadianAgents) agents*/
    for ( int i = 0; i < numOfCanadianAgent; i++ )
    {
        agents[i] .SetIsCanadianAgent(true);
    }
    
    for (int i = 0; i < numOfVisitorAgent; i++)
    {
        agents[i+numOfCanadianAgent] .SetIsCanadianAgent(false);
    }
    
}

Agents::~Agents()
{
    delete agents;
}

/*When starting processing, each agent process synchronously*/
void Agents::Processing(WaitingQueue * wq, std::thread * tAgent)
{
    for (int i = 0; i < numOfCanadianAgent; i++)
    {
        if (isStrategyOne)
        {
            tAgent[i]=agents[i].Processing(wq->GetQueue(0));
        }
        else
        {
            tAgent[i] = agents[i].Processing(wq->GetQueue(i));
        }
    }
    
    for (int i = numOfCanadianAgent; i < agentNum; i++)
    {
        if (isStrategyOne)
        {
            tAgent[i] = agents[i].Processing(wq->GetQueue(1));
        }
        else
        {
            tAgent[i] = agents[i].Processing(wq->GetQueue(i));
        }
    }
}
