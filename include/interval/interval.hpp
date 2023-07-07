#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

#include <iostream>
#include <memory>

// Full Interval
class interval {
private:
  // int val;
  int _s;
  int _e;
  int _l;
  std::shared_ptr<interval> prev;

public:
  // const int s;
  // const int e;
  // const int l;

  interval(int start, int end);
  ~interval() {}

  // int get_val() const;
  int s() const;
  int e() const;
  int l() const;

  // bool set_val(int v);
  void set_prev(const std::shared_ptr<interval> &prev);

  // static bool val_comp(const std::shared_ptr<interval> &x,
  //                      const std::shared_ptr<interval> &y);
  static bool start_comp(const interval &lhs, const interval &rhs);
  static bool end_comp(const interval &lhs, const interval &rhs);
};

bool operator<(const interval &lhs, const interval &rhs);
bool operator>(const interval &lhs, const interval &rhs);
std::ostream &operator<<(std::ostream &os, const interval &x);

// bool operator<(const interval &x, const interval &y);
// bool operator<=(const interval &x, const interval &y);
// bool operator>(const interval &x, const interval &y);
// bool operator>=(const interval &x, const interval &y);

#endif
