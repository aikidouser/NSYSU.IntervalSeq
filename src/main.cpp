#include <deque>
#include <iostream>
#include <map>
#include <string>

#include "interval/full.hpp"
#include "interval/interval.hpp"

std::deque<interval> get_input();

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::map;
using std::string;

int main(int argc, char *argv[]) {
  int q = 0;
  map<string, bool> arg_map;
  deque<interval> interval_seq;

  for (int i = 0; i < argc; i++) {
    string arg_str = static_cast<string>(argv[i]);

    if (arg_str == "-l")
      arg_map["longest"] = true;
    else if (arg_str == "-m")
      arg_map["most"] = true;
    else if (arg_str == "--single")
      arg_map["single"] = true;
    else if (arg_str == "--sub")
      arg_map["sub"] = true;
    else if (arg_str == "--full")
      arg_map["full"] = true;
  }

  interval_seq = get_input();

  q = miis_full_algo(interval_seq);
  if (miis_full_check(interval_seq, q)) {
    cout << "same" << endl;
  } else {
    cout << "something wrong" << endl;
  }

  return 0;
}

deque<interval> get_input() {
  deque<interval> input;
  int start = 0, end = 0;

  while (cin >> start >> end)
    input.emplace_back(interval(start, end));

  return input;
}
