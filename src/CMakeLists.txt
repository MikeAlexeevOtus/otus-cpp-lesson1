cmake_minimum_required(VERSION 3.2)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(helloworld_cli hello.cpp)
add_executable(test_version test_version.cpp)
add_executable(gtest_version gtest_version.cpp)
add_library(helloworld lib.cpp)

target_include_directories(helloworld PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(helloworld_cli PRIVATE helloworld)
target_link_libraries(test_version PRIVATE ${Boost_LIBRARIES} helloworld)
target_link_libraries(gtest_version PRIVATE
    gtest
    gtest_main
    helloworld
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(helloworld_cli helloworld test_version gtest_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    set(COMPILE_OPTS /W4)

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
else ()
    set(COMPILE_OPTS -Wall -Wextra -pedantic -Werror)
endif()

target_compile_options(helloworld_cli PRIVATE ${COMPILE_OPTS})
target_compile_options(helloworld PRIVATE ${COMPILE_OPTS})
target_compile_options(test_version PRIVATE ${COMPILE_OPTS})

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mike.42.alexeev@yandex.ru)

include(CPack)

add_test(test_version test_version)
add_test(gtest_version gtest_version)
