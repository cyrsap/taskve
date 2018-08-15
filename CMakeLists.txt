cmake_minimum_required(VERSION 3.12)
project(taskve)

include("conanbuildinfo.cmake")

set(CMAKE_CXX_STANDARD 17)

conan_basic_setup()

add_executable(taskve main.cpp Hasher.cpp Hasher.h)
target_link_libraries(taskve pthread ${CONAN_LIBS})