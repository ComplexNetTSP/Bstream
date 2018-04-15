SET(TEST_TIMEINTERVALSET_SRC_FILES
        ../../src/tinterval/TimeIntervalSet.cpp
        timeintervalset_tests.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

ADD_EXECUTABLE(test_timeintervalset ${TEST_TIMEINTERVALSET_SRC_FILES})

#TARGET_LINK_LIBRARIES(test_timeintervalset pybstream)

ADD_TEST(NAME testTimeIntervalSet COMMAND test_timeintervalset)