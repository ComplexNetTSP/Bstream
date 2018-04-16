###
SET(TEST_BIPARTITE_SRC_FILES
        bipartite_tests.cpp
        ../../src/graph/GraphBase.cpp
        ../../src/graph/BipartiteBase.cpp)

ADD_EXECUTABLE(test_bipartite ${TEST_BIPARTITE_SRC_FILES})

#TARGET_LINK_LIBRARIES(test_graph pybstream)

ADD_TEST(NAME testBipartite COMMAND test_bipartite)