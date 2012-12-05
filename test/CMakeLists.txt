include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_BINARY_DIR}/lib)

set(TEST_SRCS main.cpp test_atomic.cpp test_byteorder.cpp test_random.cpp test_octets.cpp test_octetstream.cpp)
add_executable(test ${TEST_SRCS})
target_link_libraries(test libzbase.a)
target_link_libraries(test /usr/lib/libgtest.a pthread)

