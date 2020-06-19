#include <ics46/factory/DynamicFactory.hpp>
#include<gsolver.hpp>
#include "MazeSolver.hpp"
#include "Direction.hpp"
#include "Maze.hpp"
#include<MazeSolution.hpp>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Gsolver, "G's solution(Required)");

Gsolver::Gsolver()
{}

//done
 void Gsolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
 {
 
    visited.push_back(mazeSolution.getStartingCell());
    process(maze,mazeSolution);
 }


//done
bool Gsolver::removeable(const Maze& maze, int x, int y, Direction direction)
{



    std::pair<int,int> next(x,y);

    if (maze.wallExists(x,y,direction))
    {
        return false;
    }
    if (direction==Direction::up)
    {
        next.second=next.second-1;


    }
    if (direction==Direction::down)
    {
       next.second=next.second+1;

    }
    if (direction==Direction::left)
    {
        next.first=next.first-1;

    }
    if (direction==Direction::right)
    {
        next.first=next.first+1;

    }    


    if(!(std::find(visited.begin(), visited.end(), next) == visited.end()))
    {
        return false;

    }
    return true;

}

void Gsolver::moving(const Maze& maze, MazeSolution& mazeSolution)
{
        std::pair<int,int> currentCell= mazeSolution.getCurrentCell();

        int tempx=currentCell.first;
        int tempy=currentCell.second;
        if (isend(maze,currentCell))
        {
            mazeSolution.backUp();
        }
        else
        {
            int directionint = distribution(engine);
            
            if (directiontype[directionint]==Direction::up)
                tempy-=1;
            if (directiontype[directionint]==Direction::down)
                tempy+=1;
            if (directiontype[directionint]==Direction::left)
                tempx-=1;
            if (directiontype[directionint]==Direction::right)
                tempx+=1;


            if (removeable(maze,currentCell.first,currentCell.second,directiontype[directionint]))
            {
                mazeSolution.extend(directiontype[directionint]);
                visited.push_back(std::pair<int,int> (tempx, tempy));
            }
    

        }

}

void Gsolver::process(const Maze& maze, MazeSolution& mazeSolution)
{
    moving(maze, mazeSolution);



    if (!mazeSolution.isComplete())
    {
        process(maze,mazeSolution);
    }
}







//done
bool Gsolver::isend(const Maze& maze,std::pair<int,int> currentCell)
{

    int x=currentCell.first;
    int y=currentCell.second;
    int pathcount=0;
    if (maze.wallExists( x,  y, Direction::up))
        pathcount++;
    else
    {
        std::pair<int,int> next(x,y-1);
        if(!(std::find(visited.begin(), visited.end(), next) == visited.end()))
            pathcount++;
    }
    
//=====================================================
    if (maze.wallExists( x,  y, Direction::down))
        pathcount++;
    else
    {
        std::pair<int,int> next(x,y+1);
        if(!(std::find(visited.begin(), visited.end(), next) == visited.end()))
            pathcount++;
    }

//=====================================================
    if (maze.wallExists( x,  y, Direction::left))
        pathcount++;
    else
    {
        std::pair<int,int> next(x-1,y);
        if(!(std::find(visited.begin(), visited.end(), next) == visited.end()))
            pathcount++;
    }
//=====================================================

    if (maze.wallExists( x,  y, Direction::right)) 
        pathcount++;
    else
    {
        std::pair<int,int> next(x+1,y);
        if(!(std::find(visited.begin(), visited.end(), next) == visited.end()))
            pathcount++;
    }
//=====================================================
    if (pathcount>=4)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}