#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>

#include "full.hpp"

using std::cout;
using std::deque;
using std::endl;
using std::make_shared;
using std::prev;
using std::shared_ptr;
using std::upper_bound;

int full::get_val() { return val; }

bool operator<(const full &lhs, const full &rhs) {
  return lhs.s < rhs.s && lhs.e < rhs.e && lhs.e < rhs.s;
}
bool operator>(const full &lhs, const full &rhs) {
  return lhs.s > rhs.s && lhs.e > rhs.e && lhs.e > rhs.s;
}

bool full::val_comp(const shared_ptr<full> &x, const shared_ptr<full> &y) {
  return x->val < y->val;
}

int miis_full_algo(const deque<interval> &interval_seq) {
  deque<shared_ptr<full>> T;

  T.emplace_back(make_shared<full>(interval_seq.at(0)));
  for (size_t i = 1; i < interval_seq.size(); i++) {
    shared_ptr<full> cur_interval = make_shared<full>(interval_seq.at(i));
    auto it = upper_bound(T.begin(), T.end(), cur_interval, full::val_comp);

    if (it == T.begin()) {
      *it = cur_interval;
    } else if (cur_interval->s > (*prev(it))->e) {
      if (it == T.end()) {
        T.push_back(cur_interval);
      } else {
        *it = cur_interval;
      }
      cur_interval->set_prev(*prev(it));
    }
    cout << "T: ";
    for (auto j : T)
      cout << j->get_val() << ", ";
    cout << endl;
  }
  return T.size();
}

bool miis_full_check(const deque<interval> &interval_seq, const int &q) {
  bool check_a = false, check_b = false;

  check_a = miis_full_comb(interval_seq, q);
  check_b = miis_full_comb(interval_seq, q + 1);

  return check_a == true && check_b == false;
}

bool miis_full_comb(const std::deque<interval> &interval_seq, const int &q) {
  bool check = false;
  int n = interval_seq.size();
  deque<full> buffer;
  deque<bool> mask(q, true);
  mask.resize(n, false);

  do {
    buffer.clear();
    for (int i = 0; i < n; i++) {
      if (mask[i]) {
        if (buffer.empty()) {
          buffer.emplace_back(full(interval_seq.at(i)));
        } else {
          full f_interval = full(interval_seq.at(i));
          if (buffer.back() < f_interval)
            buffer.push_back(f_interval);
          else
            break;
        }
      }
    }
    for (auto i : buffer)
      cout << i.get_val() << " ";
    cout << endl;
    if (buffer.size() == q)
      return true;
  } while (std::prev_permutation(mask.begin(), mask.end()));

  return check;
}
