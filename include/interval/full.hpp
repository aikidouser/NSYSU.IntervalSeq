#ifndef __FULL_HPP__
#define __FULL_HPP__

#include <deque>
#include <memory>

#include <interval/interval.hpp>

int miis_full_algo(const std::deque<interval> &interval_seq);
bool miis_full_check(const std::deque<interval> &interval_seq, const size_t &q);
bool miis_full_comb(const std::deque<interval> &interval_seq, const size_t &q);

int liis_full_algo(const std::deque<interval> &interval_seq);

#endif
