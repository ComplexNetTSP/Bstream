cmake_minimum_required(VERSION 3.9.2)
project(bstream VERSION 0.1.1)

# enable tests
include(CTest)
enable_testing()

# option
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
SET(PYBIND11_CPP_STANDARD -std=c++1z)
SET(CMAKE_CXX_FLAGS "-O0 -Wall -pedantic -pthread -std=c++1z")
SET(CMAKE_VERBOSE_MAKEFILE off)
if(CODE_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    MESSAGE("-- Enable code coverage " ${CMAKE_CXX_FLAGS})
endif()
unset(CODE_COVERAGE)

# add libary

FIND_PACKAGE(PythonInterp 3 REQUIRED)
if (PYTHONINTERP_FOUND)
    MESSAGE("-- Found Python 3 interpretor: " ${PYTHON_EXECUTABLE})
    EXECUTE_PROCESS(
            COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())"
            OUTPUT_VARIABLE DUMMY
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    SET(PYTHON_INCLUDE_DIRS ${DUMMY})
    MESSAGE("-- Found Python 3 include dir: " ${PYTHON_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})
    EXECUTE_PROCESS(
            COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig as sysconfig; import os; print(os.path.join(sysconfig.get_config_var('LIBDIR'), sysconfig.get_config_var('LDLIBRARY')))"
            OUTPUT_VARIABLE DUMMY
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    SET(PYTHON_LIBRARIES ${DUMMY})
    MESSAGE("-- Found Python 3 library: " ${PYTHON_LIBRARIES})
    LINK_LIBRARIES(${PYTHON_LIBRARIES})
endif()

FIND_PACKAGE(PythonLibs 3 REQUIRED)

FIND_PATH(PYBIND11_INCLUDE_DIRS pybind11/pybind11.h
        ${PYTHON_INCLUDE_DIRS}
        /usr/local/include
        /usr/include)

if (PYBIND11_INCLUDE_DIRS)
    MESSAGE("-- Found pybind11: " ${PYBIND11_INCLUDE_DIRS})
else()
    MESSAGE("-- Error pybind11 not found")
endif()

set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost COMPONENTS system graph REQUIRED)
if (Boost_FOUND)
    MESSAGE("-- Found Boost " ${Boost_MAJOR_VERSION} "." ${Boost_MINOR_VERSION} " include directory:\t" ${Boost_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
endif()

# The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES
        "src/graph/*.cpp"
        "src/algorithms/*.cpp"
        "src/tinterval/*.cpp")
file(GLOB SOURCES_INTERFACE "src/interface/*.cpp")

SET(SRC_INCLUDE_DIR
        "src/graph"
        "src/interface"
        "src/tinterval"
        "src/algorithms"
        "src/matrix"
        "src/utils")
INCLUDE_DIRECTORIES(${SRC_INCLUDE_DIR})
#
# Build target
#
#LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

ADD_LIBRARY(pybstream SHARED
        ${SOURCES}
        ${SOURCES_INTERFACE})

SET_TARGET_PROPERTIES(pybstream
        PROPERTIES
        PREFIX ""
        )

if (WIN32)
    # .PYD file extension on Windows
    SET_TARGET_PROPERTIES(pybstream PROPERTIES SUFFIX ".pyd")
elseif (UNIX)
    # .SO file extension on Linux/Mac OS
    SET_TARGET_PROPERTIES(pybstream PROPERTIES SUFFIX ".so")
endif()

#
# add tests cases
#
ADD_SUBDIRECTORY(tests)

#
# REMOVE GCOV and GCDA files in make clean
#
FILE (GLOB_RECURSE Test_GCDA ${PROJECT_BINARY_DIR}/*.gcda)
LIST (APPEND Test_COVERAGE_DATA "${Test_GCDA}")
FILE (GLOB_RECURSE Test_GCOV ${PROJECT_BINARY_DIR}/*.gcov)
LIST (APPEND Test_COVERAGE_DATA "${Test_GCOV}")
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${Test_COVERAGE_DATA}")

#
# Sphinx build
#
FIND_PACKAGE(Sphinx)

# configured documentation tools and intermediate build results
SET(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")

# Sphinx cache with pickled ReST documents
SET(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

# HTML output directory
SET(SPHINX_HTML_DIR "${CMAKE_SOURCE_DIR}/docs")

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/conf.py"
        "${BINARY_BUILD_DIR}/conf.py"
        @ONLY)

FILE(MAKE_DIRECTORY "${BINARY_BUILD_DIR}/_static")
FILE(MAKE_DIRECTORY "${BINARY_BUILD_DIR}/_templates")

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/index.rst"
        "${BINARY_BUILD_DIR}/index.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/index.rst"
        "${BINARY_BUILD_DIR}/reference/index.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/classes/index.rst"
        "${BINARY_BUILD_DIR}/reference/classes/index.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/classes/graph.rst"
        "${BINARY_BUILD_DIR}/reference/classes/graph.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/classes/digraph.rst"
        "${BINARY_BUILD_DIR}/reference/classes/digraph.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/classes/bipartite.rst"
        "${BINARY_BUILD_DIR}/reference/classes/bipartite.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/algorithms/generators.rst"
        "${BINARY_BUILD_DIR}/reference/algorithms/generators.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/algorithms/index.rst"
        "${BINARY_BUILD_DIR}/reference/algorithms/index.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/reference/algorithms/index.rst"
        "${BINARY_BUILD_DIR}/reference/algorithms/index.rst"
        COPYONLY)

CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/source/license.rst"
        "${BINARY_BUILD_DIR}/license.rst"
        COPYONLY)

ADD_CUSTOM_TARGET(doc ALL
        ${SPHINX_EXECUTABLE}
        -q -b html
        -c "${BINARY_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${BINARY_BUILD_DIR}"
        "${SPHINX_HTML_DIR}"
        COMMENT "Building HTML documentation with Sphinx")
add_dependencies(doc pybstream)