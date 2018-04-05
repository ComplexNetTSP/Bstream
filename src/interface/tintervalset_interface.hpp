///-------------------------------------------------------------------------------------------------
///
/// @file       tintervalset_interface.cpp
/// @brief      Python wrapper for the TimeInterval and TimeInteravalSet class
/// @author     Vincent Gauthier <vgauthier@luxbulb.org>
/// @date       04/04/2018
/// @version    0.1
/// @copyright  MIT
///
///-------------------------------------------------------------------------------------------------


#include "TimeIntervalSet.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void tinterval_interface(py::module &m)
{
    py::class_<bs::TimeInterval> ti(m, "TimeInterval");
    ti.def(py::init<>());
    ti.def("lower", &bs::TimeInterval::lower);
    ti.def("upper", &bs::TimeInterval::upper);
    ti.def("__repr__", [](bs::TimeInterval &ti) {
        std::ostringstream stream;
        stream << "<class TimeInterval ["  << ti.lower() << "," << ti.upper() << ") >";
        return stream.str();
    });
}

void tintervalset_interface(py::module &m)
{
    py::class_<bs::TimeIntervalSet> tis(m, "TimeIntervalSet");
    tis.def(py::init<>());
    tis.def(py::init<time_t, time_t>());
    tis.def("interval_def", &bs::TimeIntervalSet::interval_def);
    tis.def("set_interval_def", &bs::TimeIntervalSet::set_interval_def);
    tis.def("append", &bs::TimeIntervalSet::append);
    tis.def("size", &bs::TimeIntervalSet::size);
    tis.def("length", &bs::TimeIntervalSet::length);
    tis.def("definition_length", &bs::TimeIntervalSet::definition_length);
    tis.def("erase", &bs::TimeIntervalSet::erase);
    tis.def("__len__", &bs::TimeIntervalSet::size);

    tis.def("__iter__", [](bs::TimeIntervalSet &is){
        return py::make_iterator(is.begin(), is.end());
    }, py::keep_alive<0, 1>());

    tis.def("__repr__", [](bs::TimeIntervalSet &is) {
        std::ostringstream stream;
        stream << "<class TimeIntervalSet "  << is << ">";
        return stream.str();
    });
}