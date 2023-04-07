#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

// Full Interval
class interval {
public:
  const int s;
  const int e;
  const int l;
  interval(int start, int end);
  ~interval() {}
};

#endif
