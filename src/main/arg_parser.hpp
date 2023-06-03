#ifndef __ARG_PARSER_HPP__
#define __ARG_PARSER_HPP__

#include <deque>
#include <string>

struct arg_table {
  std::string type;
  std::string comp;
  int sub_c;
  bool verb;

  arg_table(int &argc, char *argv[]);
};

bool if_opt(const std::deque<std::string> &args, const std::string &opt);
std::string get_opt(const std::deque<std::string> &args,
                    const std::string &opt);
#endif
