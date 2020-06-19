// main.cpp
//
// ICS 46 Spring 2020
// Project #2: Time Waits for No One
//
// This is the entry point for your simulation application.
//
// All of the code that makes up your simulation -- which is everything
// except for your DoublyLinkedList and Queue implementations -- should
// be in the "app" directory, though, naturally, it shouldn't all be in
// this file.  A design that keeps separate things separate is always
// part of the requirements.
#include "/home/ics46/projects/proj2/core/DoublyLinkedList.hpp"
#include "/home/ics46/projects/proj2/core/Queue.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

int main()
{ 
  

 
    int totalsimulationtime;
    std::cin>>totalsimulationtime;
    totalsimulationtime=totalsimulationtime * 60;

    int numline;
    std::cin>>numline;


    int maxlength;
    std::cin>>maxlength;


    std::vector<Queue<int>> worker;

    char workmode;
    std::cin>>workmode;
    if (workmode=='M' or workmode=='S')
    {
        for (int i=0;i<numline;i++)
        {
    //     std::cout<<"going to create worker"<<std::endl;
            worker.push_back(   Queue<int> ());
    //     std::cout<<"worker "<< i <<" created"<<std::endl;
        }
    }
    else
    {
        worker.push_back(Queue<int> ())   ; // Mode is.
    }
    
    //common
    std::vector<int> timecost;
    for (int i=0; i<numline; ++i)
    {
        int tempcost;
        std::cin>>tempcost;
        timecost.push_back(tempcost);
      //  std::cout<<"timecost for worker "<<i <<" is "<<tempcost<<std::endl;

    }

    //common
    std::vector<int> workercd; // workercd start at 0.

    for (int i=0; i<numline; ++i)
    {
   //     std::cout<<"worker cd for worker "<<i <<" "<<timecost[i]<<std::endl;    
        workercd.push_back(0);

    }






    //common
    std::vector<std::pair<int ,int >> incoming_customer;

    int in_customer_count;
    int in_customer_time;
    std::pair<int ,int> tempcustomer;

    while(true)
    {
        if(std::cin>>in_customer_count>>in_customer_time)
        {
       //     std::cout<<in_customer_count<<"----"<<in_customer_time<<std::endl;

            tempcustomer.first = in_customer_count;
            tempcustomer.second= in_customer_time;
            incoming_customer.push_back(tempcustomer);  //incoming customer is for simualtion to check.
            
        }
        else
        {
            break;
        }
    }


//      ./run <examples/sample.in>my.out
//      diff my.out examples/sample.out


//========================================s
//sata
// STATS
// Entered Line    : 53
// Exited Line     : 40
// Exited Register : 32
// Avg Wait Time   : 68.12
// Left In Line    : 13
// Left In Register: 8
// Lost            : 13


    int enqueuecount=0;
    int dequeuecunt=0;
    int exitcount=0;
    int totalwaitcount=0;
    int leftinregister=0;
    int lostcount=0;
    int leftinline=0;


//=========================================

    int simulationcount=0;
   // std::cout<<"check";
    int lowcostindex=0;
    
   // int bestworker;

    int person; //create a person. left is id , right is entertime.
    std::vector<int> available; // avaiable worker
    std::cout<<"LOG"<<std::endl;
    std::cout<<"0 start"<<std::endl;

    while(simulationcount<totalsimulationtime)
    {
        //time management
        simulationcount++;
        //add to queue from command line
        for (int i=0 ; i<incoming_customer.size();i++) //i
        {
            //  std::cout<<" time-----------------------------------checking "<<std::endl;
            if (incoming_customer[i].second ==simulationcount)
            {
                //for each customer
                //std::cout<<" ERROR CHECK 1 "<<std::endl;
                for (int j=0; j<incoming_customer[i].first; j++) //j
                {
                    // std::cout<<" each customer-----------------------------------checking "<<std::endl;
                    person=incoming_customer[i].second;
                    //check if the worker is available
                    std::vector<int> smallQueue;
                    for(int k= 0; k < worker.size(); k++){
                        smallQueue.push_back(worker[k].size());
                    }
                    std::vector<int>::iterator smallest = std::min_element(std::begin(smallQueue), std::end(smallQueue));
                    int samllestindex=std::distance(std::begin(smallQueue), smallest);
                    //std::cout<<samllestindex<<"--------------------------------------"<<std::endl; 

                    if (worker[samllestindex].size()<maxlength)
                    {
                        worker[samllestindex].enqueue(person);
                        enqueuecount++;
                        std::cout<<incoming_customer[i].second <<" entered line "<< samllestindex +1 <<" length " << worker[samllestindex].size()<<std::endl;
                    //20 entered line 1 length 1

                    }
                    else
                    {
                        //if no available, do nothing.
                        std::cout<<simulationcount<<" lost"<<std::endl;
                        lostcount++;
                        
                    }
                    //clean up.
                    person=0;
                }// for end
            }//if end
        }// for end
        //enqueue end.

        //dequeue start





        for (int i=0; i<workercd.size();i++) // time management. working process.
        {

        }


        for (int i =0; i<workercd.size();i++)  // check with each worker.
        {
            if (workercd[i]>=1)
            {
                workercd[i]--;
                if (workercd[i]==0)
                {
                    exitcount++;
                    std::cout<< simulationcount <<" exited register "<< i+1 <<std::endl;
                }
            }
            else
            {
                workercd[i]=0;  //fix -1 error.
            }
            
            if (worker.size()==1) // when we have only one line.
            {
                if (!worker[0].isEmpty()) // if line is not empty
                {
                    for (int i=0;i<workercd.size();i++)  // find avaliable worker
                    {
                        if (workercd[i]<=0)
                        {
                            available.push_back(i);  //cd is 0  ready to serve.
                        }
                    }                        
                    if (available.size()>0) // if there is avaibale worker.
                    {
                        lowcostindex=available[0];
                        std::cout<<simulationcount<<" exited line 1" <<" length " << worker[0].size() - 1 <<" wait time ";
                        std::cout<<simulationcount - worker[0].front()<<std::endl;                        
                        totalwaitcount= totalwaitcount + simulationcount - worker[0].front();
                        std::cout<< simulationcount <<" entered register "<< lowcostindex+1 <<std::endl;
                        workercd[lowcostindex]=timecost[lowcostindex];  // start working. cd reset to max.
                        worker[0].dequeue();
                        dequeuecunt++;
                    }
                }
            }
            else  // if we have multi lines.
            {
                if (workercd[i]<=0 and !worker[i].isEmpty()) // if that worker is ready and line is not empty.
                {
                        std::cout<<simulationcount<<" exited line "<< i+1<<" length " << worker[i].size() - 1 <<" wait time ";
                        std::cout<<simulationcount - worker[i].front()<<std::endl;                        
                        totalwaitcount= totalwaitcount + simulationcount - worker[i].front();
                        std::cout<< simulationcount <<" entered register "<< i+1 <<std::endl;
                        workercd[i]=timecost[i];  // start working. cd reset to max.
                        worker[i].dequeue();
                        dequeuecunt++;



                }
            }            
        }
    }
        //dequeue end

    if (simulationcount==totalsimulationtime)
    {
        std::cout<<simulationcount<<" end"<<std::endl;

    }

//sata
// STATS
// Entered Line    : 53
// Exited Line     : 40
// Exited Register : 32
// Avg Wait Time   : 68.12
// Left In Line    : 13
// Left In Register: 8
// Lost            : 13
    
    for (int i=0; i<workercd.size(); i++)

    {
        if (workercd[i]!=0)
        {
            leftinregister++;

        }
    }

    for (int i=0;i<worker.size();i++)
    {
        leftinline=leftinline + worker[i].size();

    }

    std::cout<<"STATS"<<std::endl;
    std::cout<<"Entered Line    : "<<enqueuecount<<std::endl;
    std::cout<<"Exited Line     : "<<dequeuecunt<<std::endl;
    std::cout<<"Exited Register : "<<exitcount<<std::endl;
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2);
    std::cout<<"Avg Wait Time   : "<<double(totalwaitcount)/double(dequeuecunt)<<std::endl;
    std::cout<<"Left In Line    : "<<leftinline<<std::endl;
    std::cout<<"Left In Register: "<<leftinregister<<std::endl;
    std::cout<<"Lost            : "<<lostcount<<std::endl;




    return 0;




}

