SET(TEST_LINKSTREAM_SRC_FILES
        linkstream_tests.cpp)

SET(TEST_CONFIGURATION_FILES edges.csv)

CONFIGURE_FILE(${TEST_CONFIGURATION_FILES} ${PROJECT_BINARY_DIR}/tests/linkstream_tests COPYONLY)
ADD_EXECUTABLE(test_linkstream ${TEST_LINKSTREAM_SRC_FILES})

TARGET_LINK_LIBRARIES(test_linkstream pybstream)

ADD_TEST(NAME testLinkstream COMMAND test_linkstream)