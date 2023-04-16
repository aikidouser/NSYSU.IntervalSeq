#include <algorithm>
#include <iostream>
#include <memory>

#include "sub.hpp"

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

bool operator<(const sub &lhs, const sub &rhs) {}
bool operator>(const sub &lhe, const sub &rhs) {}

// int miis_sub_algo(const deque<interval> &interval_seq) {
//   deque<shared_ptr<sub>> T;
//
//   T.emplace_back(make_shared<sub>(interval_seq.at(0),
//                                   interval_seq.at(0).s + sub::get_c() - 1));
//   for (size_t i = 1; i < interval_seq.size(); i++) {
//     shared_ptr<sub> cur = make_shared<sub>(interval_seq.at(i));
//     auto up = upper_bound(T.begin(), T.end(), cur, interval::val_comp);
//
//     // TODO :
//     for (auto it = up; it >= T.begin(); it--) {
//       shared_ptr<sub> pre = *prev(it);
//       if (it == T.begin()) {
//         cur->set_val(cur->s + sub::get_c() - 1);
//         *it = cur;
//       } else if (it == T.end() && cur->e >= pre->get_val() + sub::get_c()) {
//         cur->set_val(max(*prev(it)));
//         cur->set_prev(*prev(it));
//         T.push_back(cur);
//       } else {
//       }
//     }
//   }
//   return T.size();
// }
