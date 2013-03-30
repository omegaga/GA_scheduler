// Copyright (c) Jianhong Li ECNC 2013
#include "GA_Matrix.h"
#include <cstdlib>
#include <cmath>

GA_Matrix::GA_Matrix(const GA_Matrix& other) {
  matrix_ = other.matrix_;
  row_expect_ = other.row_expect_;
  col_expect_ = other.col_expect_;
}

GA_Matrix::GA_Matrix(Matrix& matrix, Expect& row_expect, Expect& col_expect) :
  matrix_(matrix),
  row_expect_(row_expect),
  col_expect_(col_expect) {}

double GA_Matrix::sigma_ = 0.5;

inline bool GA_Matrix::guess_(double prob) const {
  double rand_res = (rand() % 65536) / 65536.0;
  return (prob - rand_res > 0);
}

inline double GA_Matrix::Normalize_(int miu, int x) const {
  //double PI = 3.14159265359;
  //double ret = 1/(sigma_*sqrt(2*PI))*exp(-(x-miu)*(x-miu)/(2*sigma_*sigma_));
  //return ret / (1 / (sigma_ * sqrt(2 * PI)));
  //return -1 * (x - miu) * (x - miu) + 10;
  if (x > miu)
    return (-abs(x - miu) + 3);
  else
    return (-1.5 * abs(x - miu) + 3);
}

GA_Matrix GA_Matrix::Mutate(double prob) {
  GA_Matrix ret = *this;
  int row_count = ret.matrix_.size();
  int col_count = ret.matrix_.begin()->size();
  for (int i = 0; i != row_count; i++)
    for (int j = 0; j != col_count; j++)
      if (ret.matrix_[i][j] == 1 && guess_(prob))
        ret.matrix_[i][j] = 0;
  return ret;
}

GA_pair GA_Matrix::Crossover(double prob, GA_Matrix& other) {
  if (!guess_(prob))
    return std::make_pair(*this, other);
  GA_Matrix ret1 = *this;
  GA_Matrix ret2 = other;
  bool keep = 0;
  int row_count = matrix_.size();
  for (int i = 0; i != row_count; i++) {
    keep = !keep;
    if (keep)
      continue;

    //swap the row with another
    ret1.matrix_[i] = other.matrix_[i];
    ret2.matrix_[i] = matrix_[i];
  }
  return std::make_pair(ret1, ret2);
}

double GA_Matrix::GetFitness() {
  double ret = 0;
  int row_count = matrix_.size();
  int col_count = matrix_.begin()->size();
  Expect::iterator iter_expect = row_expect_.begin();
  for (int i = 0; i != row_count; i++) {
    int counter = 0;

    // count the amount of '1' in a row
    for (int j = 0; j != col_count; j++)
      counter += matrix_[i][j];
    ret += Normalize_(row_expect_[i], counter);
    iter_expect++;
  }
  for (int j = 0; j < col_count; j++) {
    int counter = 0;

    // count the amount of '1' in a column
    for (int i = 0; i < row_count; i++)
      counter += matrix_[i][j];
    ret += Normalize_(col_expect_[j], counter);
  }
  return ret;
}


bool GA_Matrix::operator==(GA_Matrix& other) {
  int row_count = matrix_.size();
  int col_count = matrix_.begin()->size();
  for (int i = 0; i < row_count; i++)
    for (int j = 0; j < col_count; j++)
      if (matrix_[i][j] != other.matrix_[i][j])
        return false;
  return true;
}

#ifdef _GA_DEBUG_
std::ostream& operator<<(std::ostream& out, GA_Matrix& a) {
  Matrix::iterator iter_row;
  for (iter_row = a.matrix_.begin(); iter_row != a.matrix_.end(); iter_row++) {
    Row::iterator iter_col;
    Row row = *iter_row;
    for (iter_col = row.begin(); iter_col != row.end(); iter_col++) {
      out << *iter_col << ' ';
    }
    out << std::endl;
  }
  return out;
}
#endif
