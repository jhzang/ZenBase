set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})

set(SRCS atomic.cpp byteorder.cpp random.cpp appconfig.cpp clock.cpp datetime.cpp utility.cpp octets.cpp octetstream.cpp)

add_library(zbase_shared SHARED ${SRCS})
set_target_properties(zbase_shared PROPERTIES OUTPUT_NAME zbase VERSION 1.0 SOVERSION 1)
target_link_libraries(zbase_shared boost_random)

add_library(zbase_static STATIC ${SRCS})
set_target_properties(zbase_static PROPERTIES OUTPUT_NAME zbase)
target_link_libraries(zbase_static boost_random)

install(TARGETS zbase_shared zbase_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/zbase DESTINATION include)

