#include "GA_Engine.h"
#include <cstdlib>

GA_Engine::GA_Engine(GA_Matrix& start, double e, double m, int size) :
  prob_e(e),
  prob_m(m),
  size_(size) {
    srand(time(NULL));
    for (int i = 0; i < size_; i++) {
      GA_Matrix entity = start.Mutate(prob_m*2);
      population_.push_back(entity);
    }
}

int GA_Engine::Search_(std::vector<double>& roulette, double shuf) {
  int left = 0, right = size_;
  while ( left <= right ) {
    int mid = (left + right) / 2;
    if (roulette[mid] == shuf) return mid;
    else
      if (roulette[mid] > shuf) right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

void GA_Engine::Select() {
  int current_size = population_.size();
  std::vector<double> fitness(current_size);
  double sum = 0;
  for (int i = 0; i < current_size; i++) {
    fitness[i] = population_[i].GetFitness();
    sum += fitness[i];
  }
  std::vector<double> roulette(current_size);
  for (int i = 0; i < current_size; i++)
    roulette[i] = fitness[i] / sum;
  for (int i = 1; i < current_size; i++)
    roulette[i] += roulette[i - 1];
  std::vector<GA_Matrix> new_population;
  for (int i = 0; i < size_; i++) {
    double shuf = rand() % 65536 / 65536.0;
    //std::cout << shuf << ' ' << Search_(roulette, shuf) << std::endl;
    new_population.push_back(population_[Search_(roulette, shuf)]);
  }
  population_ = new_population;
}

void GA_Engine::Mutate() {
  int size = population_.size();
  for (int i = 0; i < size; i++)
    population_.push_back(population_[i].Mutate(prob_m));
}

void GA_Engine::Crossover() {
  for (int i = 0; i < size_ - 1; i++)
    for (int j = i; j < size_; j++) {
      GA_pair offspring = population_[i].Crossover(prob_e, population_[j]);
      if (offspring.first == population_[i] &&
          offspring.second == population_[j])
        continue;
      population_.push_back(offspring.first);
      population_.push_back(offspring.second);
    }
}

bool GA_Engine::Check() {
  for (int i = 0; i < size_-1; i++)
    if (!(population_[i] ==population_[i + 1]))
      return false;
  return true;
}

#ifdef _GA_DEBUG_
void GA_Engine::debug() {
  /*
  for (int i = 0; i < size_; i++) {
    std::cout << population_[i] << std::endl;
  }
  */
  std::cout << population_[0] << std::endl;
  std::cout << population_[0].GetFitness() << std::endl;
}
#endif
