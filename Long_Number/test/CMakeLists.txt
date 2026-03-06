set(SOURCES
    TestLongNumber.cpp
)

add_executable(test_LN ${SOURCES})

target_link_libraries(test_LN PRIVATE
    gtest_main
    gmock_main
    LN
)

add_test(testing test_LN)