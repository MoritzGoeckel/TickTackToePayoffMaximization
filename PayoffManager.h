#ifndef REGRETMEMORY
#define REGRETMEMORY

#include <string>
#include <vector>
#include <map>
#include<memory>

struct PayoffData {
  int trials;
  int payoff;

  PayoffData()
  {
    trials = 0;
    payoff = 0;
  }
} ;

class PayoffManager
{
    public:
        void modifyPayoff(std::string informationset, int action, int payoff);
        std::vector<double> getOptionPayoffs(std::string informationset, std::vector<int> options);

    private:
      std::map <std::string, std::shared_ptr<std::map<int, PayoffData> > > payoffs;
};

#endif
