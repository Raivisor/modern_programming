project(menu)

set(MENU_LIBRARY_NAME "menu_library")

add_library(${MENU_LIBRARY_NAME} "")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(app)