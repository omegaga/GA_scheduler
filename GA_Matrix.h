// Copyright (c) Jianhong Li ECNC 2013
#ifndef _GA_MATRIX_H_
#define _GA_MATRIX_H_
#define _GA_DEBUG_
#include <iostream>
#include <vector>

class GA_Matrix;

typedef std::vector< bool > Row;
typedef std::vector< Row > Matrix;
typedef std::vector< int > Expect;
typedef std::pair<GA_Matrix, GA_Matrix> GA_pair;

class GA_Matrix {
  public:
    GA_Matrix() {}
    GA_Matrix(const GA_Matrix& other);
    explicit GA_Matrix(Matrix& matrix, Expect& row_expect, Expect& col_expect);
    GA_Matrix Mutate(double prob);
    GA_pair Crossover(double prob, GA_Matrix& other);
    bool operator==(GA_Matrix& other);
    double GetFitness();
#ifdef _GA_DEBUG_
    friend std::ostream& operator<<(std::ostream& out, GA_Matrix& a);
#endif
  private:
    inline bool guess_(double prob) const;
    inline double Normalize_(int miu, int count) const;
    Matrix matrix_;
    Expect row_expect_;
    Expect col_expect_;
    static double sigma_;
};

#endif  // _GA_MATRIX_H_
