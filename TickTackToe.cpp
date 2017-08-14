#ifndef TICKTACKTOEIMPL
#define TICKTACKTOEIMPL

#include "TickTackToe.h"
#include<vector>
#include<algorithm>

TickTackToe::TickTackToe(){
  this->board = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
}

std::vector<int> TickTackToe::getPossibleActions(int player){
    auto opts = std::vector<int>();
    int index = 0;
    for(auto const& value: this->board) {
      if(value == -1)
        opts.push_back(index);
      index++;
    }
    return opts;
}

void TickTackToe::doAction(int action, int player){
  if(this->board[action] == -1)
    this->board[action] = player;
  else
    throw;
}

int TickTackToe::getResult(){

  int fieldsize = 3;

  //Diag
  if(this->board[0] != -1 && this->board[0] == this->board[4] && this->board[4] == this->board[8])
    return this->board[0];
  if(this->board[2] != -1 && this->board[2] == this->board[4] && this->board[4] == this->board[6])
    return this->board[2];

  //Streight Down
  for(int i = 0; i < fieldsize; i++){
    if(this->board[i] != -1 && this->board[i] == this->board[i + fieldsize] && this->board[i] == this->board[i + fieldsize * 2])
      return this->board[i];
  }

  //Stright Right
  for(int i = 0; i < fieldsize; i++){
    if(this->board[i * fieldsize] != -1 && this->board[i * fieldsize] == this->board[i * fieldsize + 1] && this->board[i] == this->board[i * fieldsize + 2])
      return this->board[i];
  }

  //Check draw
  if(std::all_of(this->board.begin(), this->board.end(), [](int n) { return n != -1; }))
    return this->DRAW;

  //Create a decent algorithm here

  return this->NOT_ENDED;
}

std::string TickTackToe::getInformationSet(int player){
  std::string str(this->board.size(), 0);
  std::transform(this->board.begin(), this->board.end(), str.begin(),
    [player](int n) {
      if(n == player)
        return 'I';
      if(n == -1)
        return '-';
      if(n != -1 && n != player)
        return 'F';
    });

  return str;
}

#endif
