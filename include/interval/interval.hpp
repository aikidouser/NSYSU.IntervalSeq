#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

#include <deque>
#include <iostream>
#include <memory>

// Full Interval
class interval {
private:
  // int val;
  int _s;
  int _e;
  int _l;
  size_t _idx;
  std::shared_ptr<interval> _prev;

public:
  // const int s;
  // const int e;
  // const int l;

  interval();
  interval(int start, int end, size_t idx);
  ~interval() {}

  // int get_val() const;
  int s() const;
  int e() const;
  int l() const;
  size_t idx() const;
  std::shared_ptr<interval> prev();

  // bool set_val(int v);
  void set_prev(const std::shared_ptr<interval> &prev);

  // static bool val_comp(const std::shared_ptr<interval> &x,
  //                      const std::shared_ptr<interval> &y);
  static bool start_comp(const interval &lhs, const interval &rhs);
  static bool end_comp(const interval &lhs, const interval &rhs);
  static bool start_comp_d(const interval &lhs, const interval &rhs);
};

std::deque<interval> trace(const interval &last);

bool operator<(const interval &lhs, const interval &rhs);
bool operator>(const interval &lhs, const interval &rhs);
std::ostream &operator<<(std::ostream &os, const interval &x);

// bool operator<(const interval &x, const interval &y);
// bool operator<=(const interval &x, const interval &y);
// bool operator>(const interval &x, const interval &y);
// bool operator>=(const interval &x, const interval &y);

#endif
