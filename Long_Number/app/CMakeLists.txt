set(SOURCES 
    main.cpp)

add_executable(main_app ${SOURCES})

target_link_libraries(main_app PRIVATE 
    LN
)