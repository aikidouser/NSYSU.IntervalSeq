#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

#include <memory>

// Full Interval
class interval {
private:
  int val;
  std::shared_ptr<interval> prev;

public:
  const int s;
  const int e;
  const int l;

  interval(int start, int end);
  ~interval() {}

  int get_val() const;

  bool set_val(int v);
  void set_prev(const std::shared_ptr<interval> &prev);

  static bool val_comp(const std::shared_ptr<interval> &x,
                       const std::shared_ptr<interval> &y);
};

bool operator<(const interval &lhs, const interval &rhs);
bool operator>(const interval &lhs, const interval &rhs);

// bool operator<(const interval &x, const interval &y);
// bool operator<=(const interval &x, const interval &y);
// bool operator>(const interval &x, const interval &y);
// bool operator>=(const interval &x, const interval &y);

#endif
