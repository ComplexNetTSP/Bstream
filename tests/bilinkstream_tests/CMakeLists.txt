SET(TEST_BILINKSTREAM_SRC_FILES
        bilinkstream_tests.cpp)

ADD_EXECUTABLE(test_bilinkstream ${TEST_BILINKSTREAM_SRC_FILES})

TARGET_LINK_LIBRARIES(test_bilinkstream pybstream)

ADD_TEST(NAME testBiLinkStream COMMAND test_bilinkstream)