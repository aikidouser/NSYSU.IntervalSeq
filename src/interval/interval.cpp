#include <algorithm>
#include <stdexcept>

#include "interval.hpp"

using std::shared_ptr;

interval::interval(int start, int end)
    : val(end), s(start), e(end), l(e - s + 1) {
  if (l < 1) {
    throw std::invalid_argument(
        "The start of the interval is bigger than the end.");
  }
}

int interval::get_val() { return val; }
void interval::set_prev(const shared_ptr<interval> &prev) { this->prev = prev; }

bool interval::val_comp(const shared_ptr<interval> &x,
                        const shared_ptr<interval> &y) {
  return x->val < y->val;
}

bool operator<(const interval &lhs, const interval &rhs) {
  return lhs.s < rhs.s && lhs.e < rhs.e && lhs.e < rhs.s;
}
bool operator>(const interval &lhs, const interval &rhs) {
  return lhs.s > rhs.s && lhs.e > rhs.e && lhs.e > rhs.s;
}

// bool operator<(const interval &x, const interval &y) {
//   return x.s < y.s && x.e < y.e;
// }
// bool operator<=(const interval &x, const interval &y) {
//   return x.s <= y.s && x.e <= y.e;
// }
// bool operator>(const interval &x, const interval &y) {
//   return x.s > y.s && x.e > y.e;
// }
// bool operator>=(const interval &x, const interval &y) {
//   return x.s >= y.s && x.e >= y.e;
// }
