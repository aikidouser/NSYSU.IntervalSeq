#ifndef __SUB_HPP__
#define __SUB_HPP__

#include <deque>

#include <interval/interval.hpp>

class sub : public interval {
private:
  static int c;

public:
  sub(int start, int end) : interval(start, end) {}
  sub(const interval &x) : interval(x) {}
  sub(const interval &x, int v) : interval(x) { set_val(v); }
  ~sub() {}

  static int get_c();

  static void set_c(int c);
};

bool operator<(const sub &lhs, const sub &rhs);
bool operator>(const sub &lhe, const sub &rhs);

int miis_sub_algo(const std::deque<interval> &interval_seq);
bool miis_sub_check(const std::deque<interval> &interval_seq, const int &q);

#endif
