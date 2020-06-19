#include "MazeSolver.hpp"
#include "Maze.hpp"
#include <random>
#ifndef GSOLVER_HPP
#define GSOLVER_HPP
class Gsolver:public MazeSolver
{
public:

    Gsolver();
    void process(const Maze& maze, MazeSolution& mazeSolution);
    bool removeable(const Maze& maze, int x, int y, Direction);
    bool isend(const Maze& maze,std::pair<int,int>);
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    void moving(const Maze& maze, MazeSolution& mazeSolution);


private:
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<int> distribution{0,3};
    std::vector<std::pair<int,int>> visited;//store all visted point
    const Direction directiontype[4]={Direction::up,Direction::down,Direction::left,Direction::right};  // (0,0)is the top left point
    std::vector<std::pair<int,int>> endpoint;
};

#endif // GSOLVER_HPP