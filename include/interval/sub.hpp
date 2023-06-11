#ifndef __SUB_HPP__
#define __SUB_HPP__

#include <cwchar>
#include <deque>

#include <interval/interval.hpp>

class sub : public interval {
private:
  int val;
  static int c;

public:
  sub(int start, int end) : interval(start, end) {}
  sub(const interval &x) : interval(x), val(x.e) {}
  sub(const interval &x, const int &v) : interval(x), val(v) {}
  ~sub() {}

  static int get_c();
  int get_val() const;

  bool set_val(int v);
  static void set_c(int c);

  static bool val_comp(const std::shared_ptr<sub> &x,
                       const std::shared_ptr<sub> &y);
};

bool operator<(const sub &lhs, const sub &rhs);
bool operator>(const sub &lhe, const sub &rhs);

int miis_sub_algo(const std::deque<interval> &interval_seq);
bool miis_sub_check(const std::deque<interval> &interval_seq, const int &q);
bool miis_sub_comb(const std::deque<interval> &interval_seq, const int &q);

int liis_sub_algo(const std::deque<interval> &interval_seq);
bool liis_sub_check(const std::deque<interval> &interval_seq, const size_t &l);

#endif
