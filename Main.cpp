#include <iostream>

#include "Game.h"
#include "TickTackToe.h"
#include "PayoffManager.h"

#include<string>

#include<cstdlib>

#include<memory>

struct GameMove {
  std::string informationset;
  int choosenAction;

  GameMove(std::string informationset, int choosenAction)
  {
    this->informationset = informationset;
    this->choosenAction = choosenAction;
  }
} ;

int main()
{
    auto pm = std::make_unique<PayoffManager>();

    for(int i = 0; i < 50000; i++){
        auto game = std::make_unique<TickTackToe>();
        int currentPlayer = 0;

        std::map <int, std::vector<GameMove> > playerMoves;

        while(game->getResult() == game->NOT_ENDED){

            //Get all the data
            std::string info = game->getInformationSet(currentPlayer);
            auto opts = game->getPossibleActions(currentPlayer);
            int action = std::rand() % opts.size();

            //auto wightedOpts = pm->getOptionPayoffs(info, opts);

            //for(double const &item : wightedOpts)
              //std::cout << item << std::endl;

            //Output it
            /*std::cout << "Player: " << currentPlayer << " Info: " << info
              << " Ations: " << opts.size()
              << " Choosing: " << action
              << " (" << opts[action] << ")" << std::endl;*/

            //Do the action
            game->doAction(opts[action], currentPlayer);

            if(playerMoves.find(currentPlayer) == playerMoves.end())
              playerMoves[currentPlayer] = std::vector<GameMove>();

            //Record the actions
            playerMoves[currentPlayer].emplace_back(GameMove(info, opts[action]));

            //Change player
            if(currentPlayer == 0)
              currentPlayer = 1;
            else
              currentPlayer = 0;
        }

        //Who won?
        int result = game->getResult();

        //If result is not a draw -> Record the payoffs for the payers
        if(result != game->DRAW){
          std::cout << "Game " << i << " was won by " << game->getResult() << std::endl;

          for(auto const &item : playerMoves){
              int payoff = 0; //Player lost
              if(item.first == result)
                payoff = 1; //Player won

              //Reward / punish all the action
              for(auto const &move : item.second){
                pm->modifyPayoff(move.informationset, move.choosenAction, payoff);
                //std::cout << "Player: " << item.first << " Payoff: " << payoff << " info: " << move.informationset << " Action: " << move.choosenAction << std::endl;
              }
          }
        }
        else //Its a draw
          std::cout << "Game " << i << " is a draw" << std::endl;
    }

    //Test how the algorithm would react to a situation
    auto wightedOpts = pm->getOptionPayoffs("FII-F----", {0,1,2,3,4,5,6,7,8});
    for(double const &item : wightedOpts)
      std::cout << item << std::endl;

    return 0;
}

//Compile with: g++ *.cpp -o main.exe
