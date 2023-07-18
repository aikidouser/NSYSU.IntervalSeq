#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>

#include <interval/full.hpp>
#include <interval/interval.hpp>
#include <utility>

using std::bitset;
using std::deque;
using std::map;
using std::pair;
using std::set;
using std::vector;

using std::cerr;
using std::cout;

using std::endl;
using std::lower_bound;
using std::make_pair;
using std::make_shared;
using std::pow;
using std::prev;
using std::upper_bound;

// TODO : use list to trace
int miis_full_algo(const deque<interval> &interval_seq,
                   deque<interval> &subseq) {
  deque<interval> T;

  T.push_back(interval_seq.at(0));
  for (size_t i = 1; i < interval_seq.size(); i++) {
    interval cur_interval = interval_seq.at(i);
    auto it = upper_bound(T.begin(), T.end(), cur_interval, interval::end_comp);

    if (it == T.begin()) {
      *it = cur_interval;
    } else if (cur_interval.s() > (*prev(it)).e()) {
      if (it == T.end()) {
        T.push_back(cur_interval);
      } else {
        *it = cur_interval;
      }
      it->set_prev(make_shared<interval>(*prev(it)));
    }
  }
  subseq = trace(T.back());
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

int liis_full_algo(const std::deque<interval> &interval_seq,
                   deque<interval> &subseq) {
  set<pair<int, int>> T;

  vector<int> prev_table(interval_seq.size(), -1);
  map<pair<int, int>, int> index_table;

  T.emplace(interval_seq.at(0).e(), interval_seq.at(0).l());
  index_table.emplace(make_pair(interval_seq.at(0).e(), interval_seq.at(0).l()),
                      0);
  for (size_t i = 0; i < interval_seq.size(); i++) {
    const interval &cur = interval_seq.at(i);
    pair<int, int> cur_pair(cur.s(), cur.l());
    auto s_low = lower_bound(T.begin(), T.end(), cur_pair);

    // cout << "[" << cur.s << ", " << cur.e << "] - " << cur.l << " : ";

    if (s_low == T.begin()) {
      cur_pair.first = cur.e();
    } else {
      cur_pair.first = cur.e();
      cur_pair.second += prev(s_low)->second;

      prev_table.at(i) = index_table[*prev(s_low)];
    }

    auto e_low = upper_bound(T.begin(), T.end(), cur_pair);
    if (e_low != T.begin()) {
      if (prev(e_low)->second >= cur_pair.second)
        continue;
    }
    auto it = e_low;
    while (cur_pair.second >= it->second && it != T.end()) {
      T.erase(it++);
    }
    T.insert(cur_pair);
    index_table.emplace(cur_pair, i);
  }

  int index = index_table.at(*T.rbegin());
  while (index >= 0) {
    // cout << "index: " << index << endl;
    subseq.push_front(interval_seq.at(index));
    index = prev_table.at(index);
  }
  return T.rbegin()->second;
}

bool liis_full_check(const std::deque<interval> &interval_seq,
                     const size_t &l) {
  size_t max_liis = 0;
  const size_t bitset_size = 64;
  size_t case_num = pow(2, interval_seq.size());

  if (interval_seq.size() > bitset_size)
    cerr << "too long" << endl;

  for (size_t i = 1; i <= case_num; i++) {
    pair<int, size_t> buffer(-1, 0);
    bitset<bitset_size> mask(i);

    for (size_t j = 0; j < interval_seq.size(); j++) {
      if (mask.test(j)) {
        interval cur = interval_seq.at(j);
        if (cur.s() > buffer.first) {
          buffer.first = cur.e();
          buffer.second += cur.l();
        } else {
          break;
        }
      }
    }
    max_liis = buffer.second > max_liis ? buffer.second : max_liis;
  }
  if (max_liis == l)
    return true;
  return false;
}
