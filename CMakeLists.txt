project(StdAvr CXX)
cmake_minimum_required(VERSION 3.6)

option(ENABLE_TESTS "Build tests" OFF)

if (ENABLE_TESTS)
    set(STDAVR_NAMESPACE_NAME "sut" CACHE INTERNAL "")
    set(STDAVR_INCLUDE_PREFIX "sut" CACHE INTERNAL "")
else ()
    set(STDAVR_NAMESPACE_NAME "std" CACHE STRING "Namespace to use")
    set(STDAVR_INCLUDE_PREFIX ""    CACHE STRING "Prefix for public headers")
endif ()

set(INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/include)
set(PUBLIC_HEADERS_DIR ${INCLUDE_PATH}/${STDAVR_INCLUDE_PREFIX})

function(publish_header name)
    set(impl_header ${CMAKE_CURRENT_SOURCE_DIR}/src/${name}.hpp)

    if (NOT EXISTS ${impl_header})
        message(FATAL_ERROR "Header ${impl_header} does not exist")
    endif ()

    file(RELATIVE_PATH impl_header_rel_path ${PUBLIC_HEADERS_DIR} ${impl_header})
    file(WRITE ${PUBLIC_HEADERS_DIR}/${name} "#include \"${impl_header_rel_path}\"\n")
endfunction()

publish_header(cstddef)
publish_header(cstdint)
publish_header(type_traits)
publish_header(utility)
publish_header(tuple)
publish_header(initializer_list)
publish_header(vector)
publish_header(algorithm)
publish_header(iterator)

add_compile_options(-Wall -std=c++17)

add_library(stdavr INTERFACE)
target_include_directories(stdavr INTERFACE ${INCLUDE_PATH})
target_compile_definitions(stdavr INTERFACE -DSTDAVR_NAMESPACE=${STDAVR_NAMESPACE_NAME})

if (ENABLE_TESTS)
    add_subdirectory(test/)
endif ()
