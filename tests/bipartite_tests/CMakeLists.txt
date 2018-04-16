###
SET(TEST_BIPARTITE_SRC_FILES
        bipartite_tests.cpp)

ADD_EXECUTABLE(test_bipartite ${TEST_BIPARTITE_SRC_FILES})

TARGET_LINK_LIBRARIES(test_bipartite pybstream)

ADD_TEST(NAME testBipartite COMMAND test_bipartite)