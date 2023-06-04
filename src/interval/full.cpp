#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>

#include <interval/full.hpp>

using std::cerr;
using std::cout;
using std::deque;
using std::endl;
using std::lower_bound;
using std::make_pair;
using std::make_shared;
using std::pair;
using std::prev;
using std::set;
using std::shared_ptr;
using std::upper_bound;

// TODO : use list to trace
int miis_full_algo(const deque<interval> &interval_seq) {
  deque<shared_ptr<interval>> T;

  T.emplace_back(make_shared<interval>(interval_seq.at(0)));
  for (size_t i = 1; i < interval_seq.size(); i++) {
    shared_ptr<interval> cur_interval =
        make_shared<interval>(interval_seq.at(i));
    auto it = upper_bound(T.begin(), T.end(), cur_interval, interval::end_comp);

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
  }
  return T.size();
}

bool miis_full_check(const deque<interval> &interval_seq, const size_t &q) {
  bool check_a = false, check_b = false;

  check_a = miis_full_comb(interval_seq, q);
  check_b = miis_full_comb(interval_seq, q + 1);

  return check_a == true && check_b == false;
}

bool miis_full_comb(const std::deque<interval> &interval_seq, const size_t &q) {
  bool check = false;
  int n = interval_seq.size();
  deque<interval> buffer;
  deque<bool> mask(q, true);
  mask.resize(n, false);

  do {
    buffer.clear();
    for (int i = 0; i < n; i++) {
      if (mask[i]) {
        if (buffer.empty()) {
          buffer.push_back(interval_seq.at(i));
        } else {
          if (buffer.back() < interval_seq.at(i))
            buffer.push_back(interval_seq.at(i));
          else
            break;
        }
      }
    }
    // for (auto i : buffer)
    //   cout << i.get_val() << " ";
    // cout << endl;
    if (buffer.size() == q)
      return true;
  } while (std::prev_permutation(mask.begin(), mask.end()));

  return check;
}

bool pair_comp(const pair<int, int> &lhs, const pair<int, int> &rhs) {
  if (lhs.first < rhs.first)
    return true;
  else if (lhs.first == rhs.first) {
    return lhs.second > rhs.second;
  }
  return false;
}

int liis_full_algo(const std::deque<interval> &interval_seq) {
  deque<int> trace(interval_seq.size(), -1);
  set<pair<int, int>, decltype(pair_comp) *> T(pair_comp);

  T.emplace(make_pair(interval_seq.at(0).e, interval_seq.at(0).l));
  for (size_t i = 0; i < interval_seq.size(); i++) {
    const interval &cur = interval_seq.at(i);
    pair<int, int> cur_pair(cur.s, cur.l);
    auto s_low = lower_bound(T.begin(), T.end(), cur_pair, pair_comp);

    if (s_low == T.begin()) {
      cur_pair.first = cur.e;
    } else {
      cur_pair.first = cur.e;
      cur_pair.second += prev(s_low)->second;
    }

    auto e_low = upper_bound(T.begin(), T.end(), cur_pair, pair_comp);
    if (e_low != T.begin()) {
      if (prev(e_low)->second >= cur_pair.second)
        continue;
    }
    auto it = e_low;
    while (cur_pair.second >= it->second && it != T.end()) {
      T.erase(it++);
    }
    T.insert(cur_pair);
  }
  return T.rbegin()->second;
}
