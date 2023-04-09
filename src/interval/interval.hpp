#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

#include <memory>

// Full Interval
class interval {
private:
  std::shared_ptr<interval> prev;

public:
  const int s;
  const int e;
  const int l;

  interval(int start, int end);
  ~interval() {}

  void set_prev(const std::shared_ptr<interval> &prev);
};

bool operator<(const interval &x, const interval &y);
bool operator<=(const interval &x, const interval &y);
bool operator>(const interval &x, const interval &y);
bool operator>=(const interval &x, const interval &y);

#endif
