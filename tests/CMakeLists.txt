file(GLOB_RECURSE TEST_SOURCES "src/*.c")

add_executable(tinyray-tests ${SOURCES} ${TEST_SOURCES})
add_test(tests tinyray-tests)
