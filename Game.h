#ifndef GAME
#define GAME

#include <string>
#include <vector>

class Game
{
    public:
        virtual std::vector<int> getPossibleActions(int player) = 0;
        virtual void doAction(int action, int player) = 0;
        virtual int getResult() = 0;
        virtual std::string getInformationSet(int player) = 0;

        static const int NOT_ENDED = -1;
        static const int DRAW = -2;
};

#endif
