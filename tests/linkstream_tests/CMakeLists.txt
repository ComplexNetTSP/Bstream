SET(TEST_LINKSTREAM_SRC_FILES
        linkstream_tests.cpp)

ADD_EXECUTABLE(test_linkstream ${TEST_LINKSTREAM_SRC_FILES})

TARGET_LINK_LIBRARIES(test_linkstream pybstream)

ADD_TEST(NAME testLinkstream COMMAND test_linkstream)