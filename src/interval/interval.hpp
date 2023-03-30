#ifndef __INTERVAL_HPP__
#define __INTERVAL_HPP__

// Full Interval
class interval {
private:
  int s; // start
  int e; // end
  int l; // length

public:
  interval(int start, int end);
  ~interval() {}

  // Getter
  int get_s() const;
  int get_e() const;
  int len() const;
};

#endif
