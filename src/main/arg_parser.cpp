#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "arg_parser.hpp"

using namespace std;

const string msg_warning = "[WARNING]: ";

arg_table::arg_table(int &argc, char *argv[])
    : type("most"), comp("full"), sub_c(0), verb(false) {

  if (argc > 64)
    throw runtime_error("There are too many arguments.");

  deque<string> args(argv, argv + argc);

  // if_opt(args, "--most");
  if (if_opt(args, "--longest"))
    type = "longest";
  // if_opt(args, "--full");
  if (if_opt(args, "--sub")) {
    comp = "sub";

    if (type == "most") {
      try {
        sub_c = stoi(get_opt(args, "--sub"));
      } catch (invalid_argument const &e) {
        cout << "Invalid Argument: There must be integer after --sub" << endl;
        exit(1);
      }
      if (sub_c < 0) {
        cout << "Invalid Argument: The constraint value must be greater or "
                "equal to 0."
             << endl;
        exit(1);
      }
    }
  }

  if (if_opt(args, "--verbose")) {
    verb = true;
  }
}

bool if_opt(const std::deque<std::string> &args, const std::string &opt) {
  string short_opt(opt, 1, 2);

  for (auto i : args) {
    if (i == opt || i == short_opt) {
      return true;
    }
  }
  return false;
}

string get_opt(const std::deque<std::string> &args, const std::string &opt) {
  string short_opt(opt, 1, 2);

  for (auto it = args.begin(), end = args.end(); it != args.end(); it++) {
    if (*it == opt || *it == short_opt) {
      if (++it != end) {
        return *it;
      }
    }
  }
  return "";
}
