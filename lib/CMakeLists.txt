include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(tinyray-lib SHARED ${SOURCES})

find_package(BCLib REQUIRED)
include_directories("${BCLIB_INCLUDE_DIRS}")
target_link_libraries(tinyray-lib bclib)
