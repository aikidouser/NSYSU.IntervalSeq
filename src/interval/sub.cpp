#include <algorithm>
#include <iostream>
#include <memory>

#include <interval/sub.hpp>

using std::cout;
using std::deque;
using std::endl;
using std::make_shared;
using std::max;
using std::prev;
using std::shared_ptr;
using std::upper_bound;

int sub::c;

int sub::get_c() { return sub::c; }

void sub::set_c(int c) { sub::c = c; }

bool operator<(const sub &lhs, const sub &rhs) {
  return lhs.s < rhs.s && lhs.e < rhs.e && // basic interval comparison
         lhs.get_val() + sub::get_c() <= rhs.e;
}
bool operator>(const sub &lhs, const sub &rhs) {
  return lhs.s > rhs.s && lhs.e > rhs.e && // basic interval comparison
         lhs.e >= rhs.get_val() + sub::get_c();
}

int miis_sub_algo(const deque<interval> &interval_seq) {
  deque<shared_ptr<sub>> T;

  T.emplace_back(make_shared<sub>(interval_seq.at(0),
                                  interval_seq.at(0).s + sub::get_c() - 1));

  for (size_t i = 1; i < interval_seq.size(); i++) {
    shared_ptr<sub> cur = make_shared<sub>(interval_seq.at(i));
    auto up = upper_bound(T.begin(), T.end(), cur, interval::val_comp);

    for (auto t = up; t >= T.begin(); t--) {
      if (t != T.end() && (*t)->get_val() <= cur->s + sub::get_c() - 1)
        break;
      if (t == T.begin()) {
        if (cur->set_val(cur->s + sub::get_c() - 1))
          *t = cur;
      } else {
        shared_ptr<sub> prev_t = *prev(t);

        if (!(*prev_t < *cur))
          continue;
        if (cur->set_val(max(cur->s + sub::get_c() - 1,
                             prev_t->get_val() + sub::get_c()))) {
          cur->set_prev(prev_t);
          if (t == T.end())
            T.push_back(cur);
          else
            *t = cur;
        }
      }
    }
  }
  return T.size();
}

bool miis_sub_check(const deque<interval> &interval_seq, const int &q) {
  bool check_a = false, check_b = false;

  check_a = miis_sub_comb(interval_seq, q);
  check_b = miis_sub_comb(interval_seq, q + 1);

  return check_a == true && check_b == false;
}

bool miis_sub_comb(const std::deque<interval> &interval_seq, const int &q) {
  int n = interval_seq.size();
  deque<sub> buffer;
  deque<bool> mask(q, true);
  mask.resize(n, false);

  do {
    buffer.clear();
    for (int i = 0; i < n; i++) {
      if (mask[i]) {
        sub cur = interval_seq.at(i);

        if (buffer.empty()) {
          buffer.emplace_back(sub(cur, cur.s + sub::get_c() - 1));
        } else {
          if (buffer.back() < cur)
            buffer.emplace_back(
                sub(cur, buffer.back().get_val() + sub::get_c()));
          else
            break;
        }
      }
    }
    if (buffer.size() == q)
      return true;
  } while (std::prev_permutation(mask.begin(), mask.end()));

  return false;
}
