#include <algorithm>
#include <deque>
#include <stdexcept>

#include <interval/interval.hpp>

using std::deque;
using std::shared_ptr;

interval::interval() {}

interval::interval(int start, int end, size_t idx)
    : _s(start), _e(end), _l(_e - _s + 1), _idx(idx), _prev(nullptr) {
  if (_l < 1) {
    throw std::invalid_argument(
        "The start of the interval is bigger than the end.");
  }
}

int interval::s() const { return _s; }
int interval::e() const { return _e; }
int interval::l() const { return _l; }
size_t interval::idx() const { return _idx; }
std::shared_ptr<interval> interval::prev() { return _prev; }

void interval::set_prev(const shared_ptr<interval> &prev) {
  this->_prev = prev;
}

// bool interval::val_comp(const shared_ptr<interval> &x,
//                         const shared_ptr<interval> &y) {
//   return x->val < y->val;
// }

bool interval::start_comp(const interval &lhs, const interval &rhs) {
  if (lhs.s() < rhs.s())
    return true;
  else if (lhs.s() == rhs.s())
    return lhs.e() < rhs.e();
  return false;
}
bool interval::end_comp(const interval &lhs, const interval &rhs) {
  if (lhs.e() < rhs.e())
    return true;
  else if (lhs.e() == rhs.e())
    return lhs.s() < rhs.s();
  return false;
}

deque<interval> trace(const interval &last) {
  interval cur = last;
  deque<interval> ans{last};

  while (cur.prev() != nullptr) {
    cur = *cur.prev();
    ans.push_front(cur);
  }
  return ans;
}

bool operator<(const interval &lhs, const interval &rhs) {
  return lhs.s() < rhs.s() && lhs.e() < rhs.e() && lhs.e() < rhs.s();
}
bool operator>(const interval &lhs, const interval &rhs) {
  return lhs.s() > rhs.s() && lhs.e() > rhs.e() && lhs.e() > rhs.s();
}

std::ostream &operator<<(std::ostream &os, const interval &x) {
  os << "[" << x.s() << ", " << x.e() << "]";
  return os;
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
