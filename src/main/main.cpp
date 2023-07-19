#include <deque>
#include <iostream>
#include <map>
#include <string>

#include <interval/full.hpp>
#include <interval/interval.hpp>
#include <interval/sub.hpp>

#include "arg_parser.hpp"

std::deque<interval> get_input();

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  size_t l = 0;
  size_t q = 0;
  arg_table arg_t(argc, argv);
  deque<interval> interval_seq;
  deque<interval> subseq;

  interval_seq = get_input();
  if (arg_t.type == "most") {
    cout << "MIIS - ";
    if (arg_t.comp == "full") {
      q = miis_full_algo(interval_seq, subseq);
      cout << "full: " << q << endl;
      if (miis_full_check(interval_seq, q))
        cout << "CORRECT" << endl;
      else
        cout << "ERROR" << endl;
    } else if (arg_t.comp == "sub") {
      sub::set_c(arg_t.sub_c);
      q = miis_sub_algo(interval_seq, subseq);
      cout << "sub: " << q << endl;
      if (miis_sub_check(interval_seq, q))
        cout << "CORRECT" << endl;
      else
        cout << "ERROR" << endl;
    }
  } else if (arg_t.type == "longest") {
    cout << "LIIS - ";
    if (arg_t.comp == "full") {
      l = liis_full_algo(interval_seq, subseq);
      cout << "full: " << l << endl;
      if (liis_full_check(interval_seq, l))
        cout << "CORRECT" << endl;
      else
        cout << "ERROR" << endl;
    } else if (arg_t.comp == "sub") {
      l = liis_sub_algo(interval_seq, subseq);
      cout << "sub: " << l << endl;
      if (liis_sub_check(interval_seq, l))
        cout << "CORRECT" << endl;
      else
        cout << "ERROR" << endl;
    }
  }
  cout << "subsequence: ";
  for (const auto &i : subseq)
    cout << i << ", ";
  cout << endl;
  cout << "index: ";
  for (const auto &i : subseq)
    cout << i.idx() << ", ";
  cout << endl;

  return 0;
}

deque<interval> get_input() {
  deque<interval> input;
  int start = 0, end = 0, index = 0;

  while (cin >> start >> end)
    input.emplace_back(interval(start, end, index++));

  return input;
}
