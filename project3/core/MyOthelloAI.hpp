#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloCell.hpp"
#include<vector>


#ifndef AI_HPP
#define AI_HPP
namespace jiaweny7
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
        int search(std::unique_ptr<OthelloGameState>& s, int depth);
        int eval(std::unique_ptr<OthelloGameState>& s);
        std::vector<std::pair<int,int>> findoptions(std::unique_ptr<OthelloGameState>& state);
        bool isEdge(int x, int y, std::unique_ptr<OthelloGameState>& s);
        


    private:
        int mycolor;
        
    };


}



#endif // AI_HPP
