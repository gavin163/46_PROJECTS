#include "MazeGenerator.hpp"
#include "Direction.hpp"
#include "Maze.hpp"
#include <random>
#ifndef GMAZE_HPP
#define GMAZE_HPP
class Gmaze:public MazeGenerator
{
public:
    Gmaze();
    void generateMaze(Maze& maze) override;
    void process(Maze& maze, int x, int y);
    bool allVisited(Maze &maze);  
    void movepoint( int x, int y);//move currentcell to point(x,y) and save in visited.
    bool removeable(Maze& maze, int x, int y);
    bool isend(Maze &maze,int x, int y);
    void moving(Maze& maze, int x, int y);
    
private:
private:    
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<int> distribution{0,3};
    std::vector<int> currentCell;
    std::vector<std::vector<int>> visited;//store all visted point
    const Direction directiontype[4]={Direction::up,Direction::down,Direction::left,Direction::right};  
    std::vector<std::vector<int>> endpoint;
    int currentindex=0;
};


#endif // GMAZE_HPP