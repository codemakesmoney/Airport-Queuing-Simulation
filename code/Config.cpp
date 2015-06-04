//
//  Config.cpp
//  Simulation Project
//
//  Created by 赵子扬 on 14-3-14.
//  Copyright (c) 2014年 ziyang zhao. All rights reserved.
//

#include "Config.h"
using namespace::std;

int* GenExpDist(int numOfNums, double expect)
{
    int serviceTime = 0;
    int random = 0;
     
    double rangeLeft = 0, rangeRight = 0;
    double numTemp = numOfNums;
    
    double interval = 1/numTemp;
    double possible = 0;
    
    int *serviceTimeArray =new int[numOfNums];
    
    srand((int)time(0));
    for(int i = 1; i <= numOfNums; i++)
    {
        possible = i * interval;
        rangeRight = fmin(-log (1-possible)*expect, 1000000);
     
        random = rand()%10000;
        serviceTime = rangeLeft + (rangeRight - rangeLeft) * random / 10000;
        
        serviceTimeArray[i] = serviceTime;
        rangeLeft = rangeRight;
    }
    return serviceTimeArray;
}


bool GeneratePassenger(Passenger * passenger)
{
    bool isSuccess = true;
    string line;
    int mark = 0;
    int *cServiceTime = new int[cPassNum];
    int *vServiceTime = new int[vPassNum];
    
    
    ifstream file ("/Users/zhaoziyang/Documents/study/cmpt816/simulation project/Simulation Project/sim-project.14-1.data.txt");
    if (!file.is_open())
    {
        cout<<"file does not exist!"<<endl;
        isSuccess = false;
        return isSuccess;
    }//endif
    
    
    for (int i = 0; i< passengerNum; i++)
    {
        passenger[i].SetMark0(i);
        getline (file,line) ;
        mark = atoi(line.c_str());
        passenger[i].SetMark1(mark);
    }//end for
   
    /* Sort PassengerTemp by mark */
    Passenger key;
    for (int i=0; i < passengerNum; i++)
    {
        key = passenger[i];
        int j = i-1;
        
        while(j >= 0 && (key.GetMark1() < passenger[j].GetMark1()))
        {
            passenger[j+1] = passenger[j];
            j--;
        }
        
        passenger[j+1] = key;
    }
    
    
    cServiceTime = GenExpDist(cPassNum, 40000);
    vServiceTime = GenExpDist(vPassNum, 75000);
    
    for (int i = 0; i < cPassNum; i++)
    {
        passenger[i].SetIsCanadian(true);
        passenger[i].SetServiceTime(cServiceTime[i]);
    }
    for (int i = 0; i < vPassNum; i++)
    {
        passenger[cPassNum+i].SetIsCanadian(false);
        passenger[cPassNum+i].SetServiceTime(vServiceTime[i]);
    }
    
    for (int i=0; i < passengerNum; i++)
    {
        key = passenger[i];
        int j = i-1;
        
        while(j >= 0 && (key.GetMark0() < passenger[j].GetMark0()))
        {
            passenger[j+1] = passenger[j];
            j--;
        }
        
        passenger[j+1] = key;
    }
    
    return isSuccess;
}