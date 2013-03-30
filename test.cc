#include "GA_Engine.h"
#include <iostream>
#include <fstream>
#define R_SIZE 5
#define C_SIZE 5
#define _GA_DEBUG_

int main() {
  std::ifstream ff;
  ff.open("test.in");
  Matrix aa;
  for (int i = 0; i < R_SIZE; i++) {
    Row t;
    for (int j = 0; j < C_SIZE; j++) {
      int x;
      ff >> x;
      t.push_back(x);
    }
    aa.push_back(t);
  }
  Expect row_exp(R_SIZE);
  for (int i = 0; i < R_SIZE; i++)
    ff >> row_exp[i];
  Expect col_exp(C_SIZE);
  for (int i = 0; i < C_SIZE; i++)
    ff >> col_exp[i];
  
  GA_Matrix bb(aa, row_exp, col_exp);
  GA_Engine engine(bb, 0.8, 0.02, 50);
  //engine.debug();
  int i;
  int times = 0;
  for (i = 0; i < 100; i++) {
    if (engine.Check()) {
      times++;
    }
    else
      times = 0;
    if (times == 5)
      break;
    //std::cout << "select" << std::endl;
    engine.Select();
    //engine.debug();
    //std::cout << "mutate" << std::endl;
    engine.Mutate();
    //engine.debug();
    //std::cout << "crossover" << std::endl;
    engine.Crossover();
    //engine.debug();
  }
  std::cout << "times: " << i << std::endl;
  engine.Select();
  engine.debug();
  return 0;
}
