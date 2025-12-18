set(SOURCES
    main.cpp
)

add_executable(sort_app ${SOURCES})

target_link_libraries(sort_app PRIVATE ${SORT_LIBRARY_NAME})