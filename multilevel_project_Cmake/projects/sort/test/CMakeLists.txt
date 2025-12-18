set(SOURCES
    sort_testing.cpp
)

add_executable(test_shell ${SOURCES})

target_link_libraries(test_shell PRIVATE
    gtest_main
    gmock_main
    ${SORT_LIBRARY_NAME}
)

add_test(testing test_shell)