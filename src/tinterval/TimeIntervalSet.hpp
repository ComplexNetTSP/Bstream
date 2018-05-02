///-------------------------------------------------------------------------------------------------
///
/// @file       TimeIntervalSet.h
/// @brief      Description of the TimeIntervalSet class.
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       18/03/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#ifndef BSTREAM_TIMEINTERVALSET_H
#define BSTREAM_TIMEINTERVALSET_H

#include <iostream>
#include <utility>
#include <limits>
#include <ctime>
#include <tuple>
#include <stdexcept>
#include <boost/icl/interval_set.hpp>

namespace boost::bstream
{

    typedef icl::interval_set<time_t> time_interval_set;
    typedef icl::interval_set<time_t>::interval_type TimeInterval;
    typedef icl::interval_set<time_t>::iterator iterator;

    TimeInterval make_time_interval(time_t b = 0, time_t e = 0);

    class TimeIntervalSetException : public std::runtime_error
    {
    public:
        TimeIntervalSetException(const std::string &what) : std::runtime_error(what)
        {};
    };

    /**
     * @class TIntervalSet
     * @brief
     */
    class TimeIntervalSet
    {
    public:
        static const time_t infinity = std::numeric_limits<time_t>::max();

        /**
         * @brief Default constructor, initialize an empty time interval set.
         */
        TimeIntervalSet();

        /**
         * @brief Initialize time interval set with its definition interval.
         * @param ti time_interval
         */
        TimeIntervalSet(const TimeInterval &definition) : interval_definition(definition)
        {};

        TimeIntervalSet(const TimeInterval &definition, const time_interval_set &s1) :
                interval_set(s1), interval_definition(definition)
        {};

        /**
         * @brief Initialize time interval set with its definition interval.
         * @param ti time_interval
         */
        TimeIntervalSet(const time_t &t1, const time_t &t2);

        ~TimeIntervalSet() = default;

        time_t definition_length();

        std::pair<time_t, time_t> interval_def() const;

        void set_interval_def(const time_t &t1, const time_t &t2);

        bool append(const time_t &t1, const time_t &t2);

        bool intersects(TimeIntervalSet &s1);

        TimeIntervalSet intersection(TimeIntervalSet &s2);

        unsigned size();

        time_t length();

        iterator begin()
        { return interval_set.begin(); };

        iterator end()
        { return interval_set.end(); };

        bool contains(const time_t &t1, const time_t &t2);

        void erase();

        friend std::ostream &operator<<(std::ostream &out, TimeIntervalSet &tis)
        {
            out << "{";
            for (auto it = tis.begin(); it != tis.end(); ++it) {
                if (it != --tis.end())
                    out << *it << ", ";
                else
                    out << *it;
            }

            out << "}";
            return out;
        };

    private:
        time_interval_set interval_set;
        TimeInterval interval_definition;
    };

} // end namespace boost::bstream

#endif //BSTREAM_TIMEINTERVALSET_H
