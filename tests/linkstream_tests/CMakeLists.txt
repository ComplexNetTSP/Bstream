SET(TEST_LINKSTREAM_SRC_FILES
        linkstream_tests.cpp
        ../../src/graph/GraphBase.cpp
        ../../src/graph/LinkStreamBase.cpp
        ../../src/graph/CSVReader.cpp
        ../../src/tinterval/TimeIntervalSet.cpp)

SET(TEST_CONFIGURATION_FILES edges.csv)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

CONFIGURE_FILE(${TEST_CONFIGURATION_FILES} ${PROJECT_BINARY_DIR}/tests/linkstream_tests COPYONLY)
ADD_EXECUTABLE(test_linkstream ${TEST_LINKSTREAM_SRC_FILES})

#TARGET_LINK_LIBRARIES(test_linkstream pybstream)

ADD_TEST(NAME testLinkstream COMMAND test_linkstream)