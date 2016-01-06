include_directories(include)

file(GLOB_RECURSE TEST_SOURCES "src/*.c")

add_executable(tinyray-tests ${SOURCES} ${TEST_SOURCES})
add_test(tests tinyray-tests)

target_link_libraries(tinyray-tests tinyray-lib)
