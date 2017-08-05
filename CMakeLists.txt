project(StdC++Avr CXX)
cmake_minimum_required(VERSION 3.6)

set(PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)

function(publish_header name)
    set(impl_header ${CMAKE_CURRENT_SOURCE_DIR}/src/${name}.hpp)

    if (NOT EXISTS ${impl_header})
        message(FATAL_ERROR "Header ${impl_header} does not exist")
    endif ()

    file(RELATIVE_PATH impl_header_rel_path ${PUBLIC_HEADERS_DIR} ${impl_header})
    file(WRITE ${PUBLIC_HEADERS_DIR}/${name} "#include \"${impl_header_rel_path}\"\n")
endfunction()

publish_header(tuple)

add_library(stdc++-avr INTERFACE)
target_include_directories(stdc++-avr INTERFACE ${PUBLIC_HEADERS_DIR})
