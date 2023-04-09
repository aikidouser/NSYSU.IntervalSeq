#include <algorithm>
#include <stdexcept>

#include "interval.hpp"

using std::shared_ptr;

interval::interval(int start, int end) : s(start), e(end), l(e - s + 1) {
  if (l < 1) {
    throw std::invalid_argument(
        "The start of the interval is bigger than the end.");
  }
}

void interval::set_prev(const shared_ptr<interval> &prev) { this->prev = prev; }

bool operator<(const interval &x, const interval &y) {
  return x.s < y.s && x.e < y.e;
}
bool operator<=(const interval &x, const interval &y) {
  return x.s <= y.s && x.e <= y.e;
}
bool operator>(const interval &x, const interval &y) {
  return x.s > y.s && x.e > y.e;
}
bool operator>=(const interval &x, const interval &y) {
  return x.s >= y.s && x.e >= y.e;
}
