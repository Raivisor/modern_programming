project(menu)

set(SOURCES
    src/main.cpp
    src/define_menu_items.cpp
    src/menu_function.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)