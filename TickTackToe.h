#ifndef TICKTACKTOE
#define TICKTACKTOE

#include "Game.h"

#include <string>
#include <vector>

class TickTackToe : public Game
{
    public:
        TickTackToe();

        std::vector<int> getPossibleActions(int player);
        void doAction(int action, int player);
        int getResult();
        std::string getInformationSet(int player);

    private:
      std::vector<int> board;
};

#endif
