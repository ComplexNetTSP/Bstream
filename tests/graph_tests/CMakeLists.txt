###
SET(TEST_GRAPH_SRC_FILES
        graph_tests.cpp ../../src/graph/GraphBase.cpp)

ADD_EXECUTABLE(test_graph ${TEST_GRAPH_SRC_FILES})

#TARGET_LINK_LIBRARIES(test_graph pybstream)

ADD_TEST(NAME testGraph COMMAND test_graph)