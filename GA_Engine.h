#ifndef _GA_ENGINE_H_
#define _GA_ENGINE_H_
#define _GA_DEBUG_

#include "GA_Matrix.h"
#include<vector>

typedef std::vector<GA_Matrix> Population;

class GA_Engine {
  public:
    GA_Engine() {}
    explicit GA_Engine(GA_Matrix& start, double e, double m, int size);
    void Select();
    void Mutate();
    void Crossover();
    bool Check();
#ifdef _GA_DEBUG_
    void debug();
#endif  // _GA_DEBUG_
  private:
    int Search_(std::vector<double>& roulette, double shuf);
    Population population_;
    double prob_e;
    double prob_m;
    //int max_generation_;
    int size_;
};


#endif  // _GA_ENGINE_H_
