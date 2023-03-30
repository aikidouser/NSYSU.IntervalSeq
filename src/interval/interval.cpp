#include "interval.hpp"

#include <algorithm>

interval::interval(int start, int end) {
  if (start > end) {
    std::swap(start, end);
  }
  s = start;
  e = end;
  l = e - s + 1;
}

int interval::get_s() const { return s; }
int interval::get_e() const { return e; }
int interval::len() const { return l; }
