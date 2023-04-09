#ifndef __FULL_HPP__
#define __FULL_HPP__

#include <deque>
#include <memory>

#include "interval.hpp"

class full : public interval {
  const int val;

public:
  full(const interval &x) : interval(x), val(x.e) {}

  int get_val();

  static bool val_comp(const std::shared_ptr<full> &x,
                       const std::shared_ptr<full> &y);
};

bool operator<(const full &lhs, const full &rhs);
bool operator>(const full &lhs, const full &rhs);

int miis_full_algo(const std::deque<interval> &interval_seq);
bool miis_full_check(const std::deque<interval> &interval_seq, const int &q);
bool miis_full_comb(const std::deque<interval> &interval_seq, const int &q);

#endif
