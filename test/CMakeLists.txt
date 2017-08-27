add_subdirectory(googletest/)
target_include_directories(gmock_main INTERFACE ${gtest_SOURCE_DIR}/include/)

set(SOURCES
    type_traits_test.cpp
    utility_test.cpp
    tuple_test.cpp
    vector_test.cpp
    algorithm_test.cpp
    iterator_test.cpp
)

add_executable(stdavr-test ${SOURCES})
target_link_libraries(stdavr-test stdavr gmock_main)
