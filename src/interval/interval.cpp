#include <algorithm>
#include <stdexcept>

#include "interval.hpp"

interval::interval(int start, int end) : s(start), e(end), l(e - s + 1) {
  if (l < 1) {
    throw std::invalid_argument(
        "The start of the interval is bigger than the end.");
  }
}
