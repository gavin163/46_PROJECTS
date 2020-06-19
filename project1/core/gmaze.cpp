
#include<gmaze.hpp>
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"
#include <algorithm>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, Gmaze, "G's Maze(Required)");


Gmaze::Gmaze()
{}
//end point is the right btm point.
void Gmaze::generateMaze(Maze& maze)
{

    for(int i = 0; i < 2; ++i)
        currentCell.push_back(0);
    visited.clear();
    visited.push_back(currentCell);
    currentindex++;
    maze.addAllWalls();
    process(maze,currentCell[0],currentCell[1]);

}

bool Gmaze::removeable(Maze& maze, int x, int y)
{
    if (x<0 or x>maze.getWidth()-1 or y<0 or y>maze.getHeight()-1)
    {
        return false;
    }

    std::vector<int> going;
    going.push_back(x);
    going.push_back(y);

    if(std::find(visited.begin(), visited.end(), going) == visited.end()) //== means not in
        return true;
    else
        return false;
}

bool Gmaze::isend(Maze& maze,int x, int y)
{
    int pathcount=0;
    for (int i=0;i<visited.size();i++)
    {
        if (visited[i][0]==x+1 and visited[i][1]==y)
            pathcount++;
        if (visited[i][0]==x-1 and visited[i][1]==y)
            pathcount++;
        if (visited[i][0]==x and visited[i][1]== y-1)
            pathcount++;
        if (visited[i][0]==x and visited[i][1]==y + 1) 
            pathcount++;
    }

    if ((x==0 and y==0) or (x==maze.getWidth()-1 and y==maze.getHeight()-1))
    {
        if (pathcount==2){
            return true;

        }
        else
            return false;
    }
    if ((x==0 and y==maze.getHeight()-1) or (x==maze.getWidth()-1 and y==0))
    {
        if (pathcount==2){
            return true;

        }
        else
            return false;
    }
    if (x==0 or y==0 or x==maze.getWidth()-1 or y==maze.getHeight()-1)
    {
        if (pathcount==3)
        {
            return true;
        }
        else
            return false;

    }

    if(pathcount==4)
        return true;
    
    return false;

    
}

bool Gmaze::allVisited(Maze &maze)
{
    if (visited.size()==maze.getHeight()*maze.getWidth())
        return true;
    else
        return false;
}

void Gmaze::moving(Maze& maze, int x, int y)
{
    int tempx=currentCell[0];
    int tempy=currentCell[1];
    if (isend(maze,currentCell[0],currentCell[1]))
            {
                currentindex--;
                currentCell=visited[currentindex];
            }
    else
    {
        tempx=currentCell[0];
        tempy=currentCell[1];
        int directionint = distribution(engine);
        
        if (directiontype[directionint]==Direction::up)
            tempy-=1;
        if (directiontype[directionint]==Direction::down)
            tempy+=1;
        if (directiontype[directionint]==Direction::left)
            tempx-=1;
        if (directiontype[directionint]==Direction::right)
            tempx+=1;
        


        if (removeable(maze,tempx,tempy))
        {
            maze.removeWall(currentCell[0],currentCell[1],directiontype[directionint]);
            movepoint(tempx,tempy);
        }
        
    }

}
void Gmaze::process(Maze& maze, int x, int y)
{
    moving(maze,x,y);

    if (!allVisited(maze))
    {
        process(maze,currentCell[0],currentCell[1]);
    }
}




void Gmaze::movepoint(int x, int y)
{
    currentCell[0]=x;
    currentCell[1]=y;
    visited.push_back(currentCell);
    currentindex=visited.size()-1;

}
