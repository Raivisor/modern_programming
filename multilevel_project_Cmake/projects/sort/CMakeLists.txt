project(sort)

set(SORT_LIBRARY_NAME "sort_library")

add_library(${SORT_LIBRARY_NAME} "")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)