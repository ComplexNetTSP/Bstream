###
SET(TEST_BIPARTITE_SRC_FILES
        bipartite_tests.cpp
        ../../src/graph/GraphBase.cpp
        ../../src/graph/BipartiteBase.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 --coverage")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

ADD_EXECUTABLE(test_bipartite ${TEST_BIPARTITE_SRC_FILES})

#TARGET_LINK_LIBRARIES(test_graph pybstream)

ADD_TEST(NAME testBipartite COMMAND test_bipartite)