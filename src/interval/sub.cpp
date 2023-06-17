#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <tuple>

#include <interval/sub.hpp>

using std::bitset;
using std::cerr;
using std::cout;
using std::deque;
using std::endl;
using std::get;
using std::make_pair;
using std::make_shared;
using std::map;
using std::max;
using std::pair;
using std::pow;
using std::prev;
using std::set;
using std::shared_ptr;
using std::tie;
using std::tuple;
using std::upper_bound;

int sub::c;

int sub::get_val() const { return val; }
int sub::get_c() { return sub::c; }

bool sub::set_val(int v) {
  if (s <= v && v <= e) {
    val = v;
    return true;
  }
  return false;
}
void sub::set_c(int c) { sub::c = c; }

bool sub::val_comp(const shared_ptr<sub> &x, const shared_ptr<sub> &y) {
  return x->val < y->val;
}

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
    auto up = upper_bound(T.begin(), T.end(), cur, sub::val_comp);

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

bool miis_sub_comb(const std::deque<interval> &interval_seq, const size_t &q) {
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

int liis_sub_algo(const std::deque<interval> &interval_seq) {
  set<tuple<int, int, int>> T;

  const interval &temp = interval_seq.at(0);
  T.emplace(temp.e, temp.l, temp.l);
  for (size_t i = 1; i < interval_seq.size(); i++) {

    // cout << "T_start: ";
    // for (auto j : T) {
    //   cout << "(" << get<0>(j) << ", " << get<1>(j) << ", " << get<2>(j)
    //        << "), ";
    // }
    // cout << endl;

    const interval &cur = interval_seq.at(i);
    // end, interval length, LIIS length
    tuple<int, int, int> cur_tuple(cur.s, cur.l, cur.l);

    // cout << "[" << cur.s << ", " << cur.e << "] - " << cur.l << ": " << endl;

    if (T.empty()) {
      T.emplace(cur.e, cur.l, cur.l);
      continue;
    }

    auto s_low = T.lower_bound(cur_tuple);
    // get<0>(cur_tuple) = cur.e;
    // Extend
    // cout << "s_low: [" << get<0>(*s_low) << ", " << get<1>(*s_low) << "] - "
    //      << get<2>(*s_low) << ": " << endl;
    if (s_low == T.begin()) { // The first
      // cout << "T_begin" << endl;
      get<0>(cur_tuple) = cur.e;
      if (cur.s > get<0>(*s_low) - get<1>(*s_low) + 1 &&
          get<0>(cur_tuple) > get<0>(*s_low)) {
        get<1>(cur_tuple) = get<1>(*s_low) + get<0>(cur_tuple) - get<0>(*s_low);
        get<2>(cur_tuple) = get<1>(cur_tuple);
        T.erase(s_low);
      }
    } else if (s_low == T.end()) { // Only can extend by predecessor
      // cout << "T_end" << endl;
      get<0>(cur_tuple) = cur.e;
      get<2>(cur_tuple) += get<2>(*prev(s_low));
    } else { // Check both predecessor and successor
      // cout << "else" << endl;
      int pred_len = cur.l + get<2>(*prev(s_low));
      // cout << "pred_len: " << pred_len << endl;
      int succ_len = 0;
      if (cur.s > get<0>(*s_low) - get<1>(*s_low) + 1 && cur.e > get<0>(*s_low))
        succ_len = cur.e - get<0>(*s_low) + get<2>(*s_low);
      //  cout << "succ_len: " << succ_len << endl;
      get<0>(cur_tuple) = cur.e;
      if (pred_len > succ_len)
        get<2>(cur_tuple) = pred_len;
      else {
        get<1>(cur_tuple) = succ_len;
        get<2>(cur_tuple) = succ_len;
        T.erase(s_low);
      }
    }
    // cout << "(" << get<0>(cur_tuple) << ", " << get<1>(cur_tuple) << ", "
    //      << get<2>(cur_tuple) << ")" << endl;

    // Domination
    auto e_low = T.upper_bound(cur_tuple);
    // cout << "e_low: [" << get<0>(*e_low) << ", " << get<1>(*e_low) << "] - "
    //      << get<2>(*e_low) << ": " << endl;
    // been dominated
    if (e_low != T.begin()) {
      if (get<2>(*prev(e_low)) >= get<2>(cur_tuple)) {
        // cout << "been dominated" << endl << endl;
        continue;
      }
    } else if (e_low != T.end()) {
      if (get<0>(*e_low) - get<1>(*e_low) + 1 <=
          get<0>(cur_tuple) - get<1>(cur_tuple) + 1) {
        // cout << "been cover" << endl << endl;
        continue;
      }
    }

    // dominiate
    auto it = e_low;
    while (it != T.end() && get<2>(cur_tuple) >= get<2>(*it)) {
      // cout << "dominate others" << endl;
      T.erase(it++);
    }

    auto cur_it = T.insert(cur_tuple).first;
    // cout << "insert: (" << get<0>(*cur_it) << ", " << get<1>(*cur_it) << ", "
    //      << get<2>(*cur_it) << ")" << endl;
    if (cur_it != T.begin()) {
      // cout << "in last" << endl;
      it = prev(cur_it);
      // cout << "prev insert: (" << get<0>(*it) << ", " << get<1>(*it) << ", "
      //     << get<2>(*it) << ")" << endl;
      // cout << "prev: " << get<0>(*it) - get<1>(*it) + 1
      //      << ", cur: " << get<0>(cur_tuple) - get<1>(cur_tuple) + 1 << endl;
      if (get<1>(*it) == get<2>(*it) &&
          get<0>(cur_tuple) - get<1>(cur_tuple) + 1 <=
              get<0>(*it) - get<1>(*it) + 1) {
        // cout << "cover others" << endl;
        T.erase(it);
      }
    }

    // cout << "T: ";
    // for (auto j : T) {
    //   cout << "(" << get<0>(j) << ", " << get<1>(j) << ", " << get<2>(j)
    //        << "), ";
    // }
    // cout << endl << endl;
  }
  return get<2>(*T.rbegin());
}

bool liis_sub_check(const std::deque<interval> &interval_seq, const size_t &l) {
  size_t max_liis = 0;
  const size_t bitset_size = 64;
  size_t case_num = pow(2, interval_seq.size());

  if (interval_seq.size() > bitset_size)
    cerr << "too long" << endl;

  for (size_t i = 1; i <= case_num; i++) {
    bool if_fin = true;
    size_t length = 0;
    pair<int, int> prev(1, 0); // interval
    deque<pair<int, int>> temp;
    bitset<bitset_size> mask(i);

    for (size_t j = 0; j < interval_seq.size(); j++) {
      if (mask.test(j)) {
        interval cur = interval_seq.at(j);

        if (prev.first > prev.second) { // Init
          prev.first = cur.s;
          prev.second = cur.e;
          length = cur.l;
        } else if (cur.s > prev.first && cur.e > prev.second) {
          if (cur.s <= prev.second) {
            length += cur.e - prev.second;
            prev.second = cur.e;
          } else if (cur.s > prev.second) {
            length += cur.l;
            prev.first = cur.s;
            prev.second = cur.e;
          }
        } else {
          if_fin = false;
          break;
        }
      }
    }
    if (if_fin)
      max_liis = length > max_liis ? length : max_liis;
  }
  cout << max_liis << endl;
  if (max_liis == l)
    return true;
  return false;
}
