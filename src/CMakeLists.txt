cmake_minimum_required(VERSION 3.2)

project(helloworld VERSION 0.0.1)

add_executable(helloworld_cli hello.cpp)

set_target_properties(helloworld_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
