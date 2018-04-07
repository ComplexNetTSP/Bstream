///-------------------------------------------------------------------------------------------------
///
/// @file       timeintervalset_tests.cpp
/// @brief      Tests for the TimeIntervalSet class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       18/03/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "TimeIntervalSet.hpp"

#define BOOST_TEST_MODULE TIntervalSet_tests

#include <boost/test/included/unit_test.hpp>
#include <ctime>
#include <limits>

using namespace boost::bstream;
using namespace std;

BOOST_AUTO_TEST_CASE(constructor)
{
    time_t t1 = 0, t2 = 10;
    const TimeInterval ti = make_time_interval(t1, t2);
    vector<TimeInterval> result;

    TimeIntervalSet tsi(ti);

    auto def = tsi.interval_def();
    BOOST_CHECK(def.first == t1);
    BOOST_CHECK(def.second == t2);
    BOOST_CHECK(tsi.definition_length() == 10);
}

BOOST_AUTO_TEST_CASE(empty_constructor)
{
    auto infinity = std::numeric_limits<time_t>::max();
    TimeIntervalSet tsi;

    auto def = tsi.interval_def();
    BOOST_CHECK(def.first == 0);
    BOOST_CHECK(def.second == infinity);
    BOOST_CHECK(tsi.definition_length() == infinity);
}

BOOST_AUTO_TEST_CASE(time_t_constructor)
{
    time_t t1 = 0, t2 = 10;
    TimeIntervalSet tsi(t1, t2);

    auto def = tsi.interval_def();
    BOOST_CHECK(def.first == t1);
    BOOST_CHECK(def.second == t2);
    BOOST_CHECK(tsi.definition_length() == 10);
}


BOOST_AUTO_TEST_CASE(append)
{
    time_t t1 = 0, t2 = 10;
    const TimeInterval ti = make_time_interval(t1, t2);
    vector<TimeInterval> result;

    TimeIntervalSet tsi(ti);

    time_t ti1_begin = 1, ti1_end = 4;
    tsi.append(ti1_begin, ti1_end);
    result.push_back(make_time_interval(ti1_begin, ti1_end));

    time_t ti2_begin = 6, ti2_end = 8;
    tsi.append(ti2_begin, ti2_end);
    result.push_back(make_time_interval(ti2_begin, ti2_end));

    auto result_it = result.begin();
    for (auto it: tsi)
    {
        BOOST_CHECK(it.lower() == (*result_it).lower());
        BOOST_CHECK(it.upper() == (*result_it).upper());
        ++result_it;
    }

    BOOST_CHECK(tsi.size() == 2);

    time_t ti3_begin = 6, ti3_end = 15;
    auto ret = tsi.append(ti3_begin, ti3_end);

    BOOST_CHECK(ret == false);
    BOOST_CHECK(tsi.size() == 2);

}

BOOST_AUTO_TEST_CASE(length)
{
    time_t t1 = 0, t2 = 10;
    const TimeInterval ti = make_time_interval(t1, t2);
    vector<TimeInterval> result;

    TimeIntervalSet tsi(ti);

    time_t ti1_begin = 1, ti1_end = 4;
    tsi.append(ti1_begin, ti1_end);
    result.push_back(make_time_interval(ti1_begin, ti1_end));

    time_t ti2_begin = 6, ti2_end = 8;
    tsi.append(ti2_begin, ti2_end);
    result.push_back(make_time_interval(ti2_begin, ti2_end));

    BOOST_CHECK(tsi.length() == 5);
}

BOOST_AUTO_TEST_CASE(erase)
{
    TimeIntervalSet tsi;
    tsi.append(1, 3);
    tsi.append(5, 7);
    tsi.erase();
    BOOST_CHECK(tsi.size() == 0);
    BOOST_CHECK(tsi.length() == 0);
}

BOOST_AUTO_TEST_CASE(test_TimeInterval)
{
    auto a = make_time_interval(0,10);
    auto b = make_time_interval(0,10);
    auto c =  make_time_interval(0,6);
    BOOST_CHECK(a == b);
    BOOST_CHECK(a != c);
}