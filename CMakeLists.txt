cmake_minimum_required(VERSION 3.2)

set(TRAVIS_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
if(NOT TRAVIS_BUILD_NUMBER)
    set(TRAVIS_BUILD_NUMBER 1)
endif()

project(helloworld VERSION 0.0.${TRAVIS_BUILD_NUMBER})

enable_testing()

# exclude gtest from package
# see https://stackoverflow.com/a/51746390
set(INSTALL_GMOCK 0)
set(INSTALL_GTEST 0)

add_subdirectory(external/googletest gtest)
add_subdirectory(src helloworld)
