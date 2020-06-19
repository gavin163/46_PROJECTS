#include <ics46/factory/DynamicFactory.hpp>
#include <vector>
#include "MyOthelloAI.hpp"
#include "OthelloBoard.hpp"
#include "OthelloGameState.hpp"
#include<iostream>


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, jiaweny7::MyOthelloAI, "gsAI(Required)");

//Then the white player need only be concerned with the subtree that has the current game state as its root.
std::pair<int, int> jiaweny7::MyOthelloAI::chooseMove(const OthelloGameState& state)
{

    int totalkeys=state.blackScore() + state.whiteScore();
    if (totalkeys==4)
        mycolor=1; //black
    else if (totalkeys==5)
        mycolor=2; //white 
//======================================================================
    std::unique_ptr<OthelloGameState> bestfuture=state.clone();
    std::pair<int,int> best;
    std::unique_ptr<OthelloGameState> future=state.clone();
   // std::pair<std::pair<int,int>,int> moveit;
    std::vector<std::pair<int,int>> choices = findoptions(bestfuture);
    bestfuture->makeMove(choices[0].first,choices[0].second);
    best = choices[0];
    int depth=0;
    if (mycolor==1)
        depth=22;
    else if (mycolor==2)
        depth=11;
if ( state.blackScore()+state.whiteScore()+depth >= ((state.board().height()) * (state.board().width())))
    depth =  state.board().height() * state.board().width() - state.blackScore() - state.whiteScore();



    for (int i=0;i<choices.size();i++)
    {
        future=state.clone();
        future->makeMove(choices[i].first,choices[i].second);
        int indexsearh=search(future,depth);
        if (search(bestfuture,depth) < indexsearh)
        {
            bestfuture = state.clone();
            bestfuture->makeMove(choices[i].first,choices[i].second);
            best=choices[i];
        }
        
    }
    return best;


}


bool jiaweny7::MyOthelloAI::isEdge(int x, int y, std::unique_ptr<OthelloGameState>& s){
    if(x == 0 or y == 0 or y == s->board().height()-1 or x == s->board().width()-1)
        return true;
    else
        return false;
}

int jiaweny7::MyOthelloAI::search(std::unique_ptr<OthelloGameState>& state, int depth)
{
    
    std::vector<std::vector<int>> bestlist;

    if (depth<=0 or state->isGameOver())
        return eval(state);
    else if ( (mycolor==1 and state->isBlackTurn() )or( mycolor==2 and state->isWhiteTurn()) ) // if is my turn
        {

            std::unique_ptr<OthelloGameState> future=state->clone();
            std::vector<std::pair<int,int>> choices= findoptions(future);
            std::unique_ptr<OthelloGameState> bestfuture=state->clone();

            std::pair<int,int> best;
            bestfuture->makeMove(choices[0].first,choices[0].second);
            best = choices[0];
            std::vector<int> firstone;
            firstone.push_back(choices[0].first); firstone.push_back(choices[0].second);firstone.push_back(eval(bestfuture));
            bestlist.push_back(firstone);
            
            for(int i=0;i<choices.size();i++)
            {
                std::unique_ptr<OthelloGameState> future=state->clone();
                future->makeMove(choices[i].first,choices[i].second);
                
                if (eval(future)>eval(bestfuture))
                {
                    std::vector<int> saveit;
                    saveit.push_back(choices[i].first);saveit.push_back(choices[i].second);saveit.push_back(eval(future));
                    bestlist.push_back(saveit);
                    bestfuture=state->clone();
                    bestfuture->makeMove(choices[i].first,choices[i].second);
                    best = choices[i];
                }
            }
            int highest=bestlist[0][2];
            for (int i =0; i<bestlist.size();i++)
            {
                if (bestlist[i][2]>highest)
                {
                    highest=bestlist[i][2];
                }
            }

            std::vector<std::vector<int>> updatedbestlist;
            for (int i=0; i<bestlist.size();i++)
            {
                if (bestlist[i][2]>highest-2)
                {
                    updatedbestlist.push_back(bestlist[i]);
                }
            }

            for (int i=0;i<updatedbestlist.size();i++)
            {
                if (isEdge(updatedbestlist[i][0],updatedbestlist[i][1],state))
                {
                    bestfuture=state->clone();
                    bestfuture->makeMove(updatedbestlist[i][0],updatedbestlist[i][1]);
                    return search(bestfuture,depth-1);
                }
            }




            return search(bestfuture,depth-1);

        }
        else
        {

            std::unique_ptr<OthelloGameState> future=state->clone();
            std::vector<std::pair<int,int>> choices= findoptions(future);
            std::unique_ptr<OthelloGameState> bestfuture=state->clone();

            std::pair<int,int> best;
            bestfuture->makeMove(choices[0].first,choices[0].second);
            best = choices[0];
            
            for(int i=0;i<choices.size();i++)
            {
                std::unique_ptr<OthelloGameState> future=state->clone();
                future->makeMove(choices[i].first,choices[i].second);
                if (eval(future)<eval(bestfuture))
                {
                    bestfuture=state->clone();
                    bestfuture->makeMove(choices[i].first,choices[i].second);
                    best = choices[i];
                }

            }

            return search(bestfuture,depth-1);


            
        }
    

}


int jiaweny7::MyOthelloAI::eval (std::unique_ptr<OthelloGameState>&state)
{   
    if (mycolor==1)
        return state->blackScore() -state->whiteScore();
    return state->whiteScore() - state->blackScore();
}



std::vector<std::pair<int,int>> jiaweny7::MyOthelloAI::findoptions(std::unique_ptr<OthelloGameState>&state)
{
    std::vector<std::pair<int,int>> choice;


    for (int i=0;i<state->board().height();i++)
    {
        for (int j=0;j<state->board().width();j++)
        {
            if (state->isValidMove(i,j))
            {
                std::pair<int,int> one;
                one.first=i;
                one.second=j;
                choice.push_back(one);
            }
        }
    }

    return choice;



}