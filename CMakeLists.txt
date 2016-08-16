project(test)

set (CMAKE_CXX_FLAGS "--std=c++11 -O2")

include_directories("iter/include")

add_executable(copy_test copy_test.cpp)
