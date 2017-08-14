#ifndef REGRETMEMORYIMPL
#define REGRETMEMORYIMPL

#include <string>
#include <vector>
#include<memory>


#include"PayoffManager.h"

void PayoffManager::modifyPayoff(std::string informationset, int action, int payoff){
  if(this->payoffs.find(informationset) == this->payoffs.end())
    this->payoffs[informationset] = std::make_shared<std::map<int, PayoffData> >();

  if(this->payoffs[informationset]->find(action) == this->payoffs[informationset]->end())
    (*this->payoffs[informationset])[action] = PayoffData();

  (*this->payoffs[informationset])[action].trials++;
  (*this->payoffs[informationset])[action].payoff += payoff;
};

std::vector<double> PayoffManager::getOptionPayoffs(std::string informationset, std::vector<int> options){
  if(this->payoffs.find(informationset) != this->payoffs.end()){
    auto out = std::vector<double>();

    for(int opt : options){
      if(this->payoffs[informationset]->find(opt) != this->payoffs[informationset]->end()) //With double
        out.push_back((*this->payoffs[informationset])[opt].payoff / (double)(*this->payoffs[informationset])[opt].trials);
      else
        out.push_back(0);
    }

    return out;
  }
  else
    return {};
}

#endif
