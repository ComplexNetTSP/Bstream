//
// Created by Vincent Gauthier on 08/04/2018.
//

#ifndef BSTREAM_CVSREADER_INTERFACE_HPP
#define BSTREAM_CVSREADER_INTERFACE_HPP

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <iostream>

#include "GraphType.hpp"
#include "CSVReader.hpp"

namespace py = pybind11;
namespace bs = boost::bstream;

void csvreader_interface(py::module &m)
{
    py::class_<bs::CSVReader> cvsreader(m, "CSVReader");
    cvsreader.def(py::init<char, std::string>(), py::arg("delimiter") = ",", py::arg("comment")="#");
    cvsreader.def("read_graph", &bs::CSVReader::read_graph);
}

#endif //BSTREAM_CVSREADER_INTERFACE_HPP
