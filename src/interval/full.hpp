#include <deque>
#include <memory>

#include "interval.hpp"

class full : public interval {
  const int val;

public:
  full(const interval &x) : interval(x), val(x.e) {}

  int get_val();

  static bool val_comp(const std::shared_ptr<full> &x,
                       const std::shared_ptr<full> &y);
};

int miis_full_algo(const std::deque<interval> &interval_seq);
// int miis_full_check(const std::deque<interval> &interval_seq);
