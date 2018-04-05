///-------------------------------------------------------------------------------------------------
///
/// @file       TimeIntervalSet.cpp
/// @brief      Implementation file of the TimeIntervalSet class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       18/03/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include <boost/icl/interval_set.hpp>
#include <numeric>
#include <tuple>
#include <limits>

#include "TimeIntervalSet.hpp"

using namespace std;
using namespace boost::icl;

namespace boost::bstream
{
    TimeIntervalSet::TimeIntervalSet()
    {
        interval_definition = make_time_interval();
    }

    TimeIntervalSet::TimeIntervalSet(const time_t &t1, const time_t &t2)
    {
        interval_definition = make_time_interval(t1, t2);
    }

    bool
    TimeIntervalSet::append(const time_t &t1, const time_t &t2)
    {
        auto ti = make_time_interval(t1, t2);
        if (contains(interval_definition, ti)) {
            interval_set.insert(ti);
            return true;
        }else {
            return false;
        }
    }

    void
    TimeIntervalSet::set_interval_def(const time_t &t1, const time_t &t2)
    {
        interval_definition = make_time_interval(t1, t2);
    }

    pair<time_t, time_t>
    TimeIntervalSet::interval_def() const
    {
        auto l = interval_definition.lower();
        auto u = interval_definition.upper();
        return std::make_pair(l, u);
    }

    time_t
    TimeIntervalSet::length()
    {
        time_t sum;
        sum = accumulate(interval_set.begin(), interval_set.end(), 0,
                         [](time_t a, TimeInterval b) {
                             return a + (b.upper() - b.lower());
                         });

        return sum;
    }

    time_t
    TimeIntervalSet::definition_length()
    {
        return interval_definition.upper() - interval_definition.lower();
    }

    unsigned
    TimeIntervalSet::size()
    {
        return iterative_size(interval_set);
    }

    void TimeIntervalSet::erase()
    {
        interval_set.erase(begin(), end());
    }

    TimeInterval make_time_interval(time_t b, time_t e)
    {
        if(e == 0)
            e = std::numeric_limits<time_t>::max();
        return TimeInterval::right_open(b, e);
    }
}


