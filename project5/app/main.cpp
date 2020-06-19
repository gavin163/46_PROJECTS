 // main.cpp
//
// ICS 46 Spring 2020
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include<iostream>
#include "RoadSegment.hpp"
#include "RoadMap.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"

#include "TripReader.hpp"
#include "Trip.hpp"
#include <iomanip>
#include <map>
#include<vector>


struct vinfo
{
    int vertex;
    std::string roadname;
    RoadSegment info;

};

std::map<int, int> shortestpath(int startVertex, TripMetric metric, RoadMap roadMap)
{
    std::function<double(const RoadSegment&)> bestpath = [](RoadSegment segment){return segment.miles;};
    std::function<double(const RoadSegment&)> besttime = [](RoadSegment segment){return segment.miles/segment.milesPerHour;};

    if(metric == TripMetric::Time)
        return roadMap.findShortestPaths(startVertex, besttime);
    else
        return roadMap.findShortestPaths(startVertex, bestpath);
}


void timetranform(double insecond)
{
    int ahour = pow(60,2), amin =pow(60,1);
    int hour=0, min=0;

    while (insecond >= ahour)
    {
        if (insecond - ahour >= 0)
        {
            hour++;
            insecond = insecond - ahour ;
        }
    }

    while (insecond >= amin)
    {
        if (insecond -amin >= 0)
        {
            min++;
            insecond = insecond -amin;
        }
    }

    if (hour !=0)
    {
        if (hour == 1 )
            std::cout<< hour <<" hr ";
        else
            std::cout<< hour << " hrs ";
    }

    if (min  !=0 or hour != 0)
    {
        if (min == 1)
            std::cout << min << " min ";
        else
            std::cout << min << " mins ";
    }


    if (insecond == double(1))
        std::cout<< insecond << " sec";
    else
        std::cout<< insecond << " secs";

    


}


void printingformat(std::vector<vinfo> backTrip, RoadMap roadMap, double shortestPath,TripMetric typem){
    if (typem == TripMetric::Distance)
    {
        std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(1);     
        std::cout << "Shortest distance from " << roadMap.vertexInfo(backTrip.back().vertex) << " to " << roadMap.vertexInfo(backTrip.front().vertex) <<std::endl;
        std::cout << "  Begin at " << backTrip.back().roadname << std::endl;
        for (int i = backTrip.size()-1 ; i >= 1 ;i--)
        {
            if (backTrip[i].info.miles != 1)
                std::cout << "  Continue to " << backTrip[i-1].roadname <<" ("<< backTrip[i].info.miles << " miles)" << std::endl;
            else
            {
                std::cout << "  Continue to " << backTrip[i-1].roadname <<" ("<< backTrip[i].info.miles << " mile)" << std::endl;
            }
            
        }
        if (shortestPath != 1)
            std::cout << "Total distance: " << shortestPath << " miles" <<std::endl<<std::endl;
        else
        {
            std::cout << "Total distance: " << shortestPath << " mile" <<std::endl<<std::endl;
        }
        
    }
    else
    {   
        double totaltime=0;

        std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(1);
        std::cout << "Shortest driving time from " << roadMap.vertexInfo(backTrip.back().vertex) << " to " << \
                                                    roadMap.vertexInfo(backTrip.front().vertex) <<std::endl;
        std::cout << "  Begin at " << backTrip.back().roadname << std::endl;
        for (int i = backTrip.size()-1 ; i >= 1 ;i--)
        {
            double timeInSecond = backTrip[i].info.miles / backTrip[i].info.milesPerHour * 3600.0;
            std::cout << "  Continue to " << backTrip[i-1].roadname <<" ("<< backTrip[i].info.miles << " miles @ ";
            std::cout << backTrip[i].info.milesPerHour << "mph = ";
            timetranform(timeInSecond);
            totaltime+= timeInSecond;
            std::cout << ")" << std::endl;

        }
        std::cout << "Total time: ";
        timetranform(totaltime);
        std::cout<<std::endl<<std::endl;
    }
}



void run()
{
    
 //   std::cout<<"error check -2"<<std::endl; 
//loading......
    InputReader ir = InputReader(std::cin);
//=============================================
    RoadMapReader  rmr;
    RoadMap rmap = rmr.readRoadMap(ir);
//=============================================
    TripReader tr;
    std::vector<Trip> triplist = tr.readTrips(ir);
//================================================
   // std::cout<<"error check -1"<<std::endl;



   if (! rmap.isStronglyConnected())
   {
       std::cout<<"Disconnected Map"<<std::endl;
       return;
   }


    std::map<int,int> pathinfo;

    for (int i = 0; i<triplist.size();i++)
    {
   //     std::cout<<"error check 1"<<std::endl;

        TripMetric typem =triplist[i].metric;
        int endVertex = triplist[i].endVertex;
        int startVertex = triplist[i].startVertex;
        pathinfo = shortestpath(startVertex,typem,rmap);






        //end version
// ./run <inputs/sample.txt> output.txt

        vinfo endvinfo{endVertex, rmap.vertexInfo(endVertex), rmap.edgeInfo(pathinfo[endVertex], endVertex)};
        std::vector<vinfo> backtrip{endvinfo};
        double shortestPath = endvinfo.info.miles;
        while(endVertex != startVertex){
            int prevE = endVertex;
            endVertex = pathinfo[endVertex];
            backtrip.push_back(vinfo{endVertex, rmap.vertexInfo(endVertex), rmap.edgeInfo(endVertex, prevE)});
            if(endVertex != startVertex)
                shortestPath+= rmap.edgeInfo(endVertex, prevE).miles;
        }


        printingformat(backtrip,rmap,shortestPath,typem);


    }
}

int main()
{

    run();
    return 0;
}

