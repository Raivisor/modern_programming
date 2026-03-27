project(containers)

set(CONTAINERS_LIB "containers_lib")
add_library(${CONTAINERS_LIB} STATIC "")

enable_testing()

add_subdirectory(lib/googletest)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
