set(SOURCES
    main.cpp
)

add_executable(menu_app ${SOURCES})

target_link_libraries(menu_app PRIVATE ${MENU_LIBRARY_NAME})

