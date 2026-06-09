# git https://github.com/ThanCoder/dual_store_cpp.git

cmake_minimum_required(VERSION 3.10)
project(dual_store VERSION 0.0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)


add_library(libs STATIC src/libs/dualstore_encoder.cpp
    src/libs/dualstore_decoder.cpp
    src/libs/dualstore_decoder.h)

target_include_directories(libs PUBLIC src/libs)

add_executable(dual_store src/main.cpp)


target_link_libraries(dual_store PRIVATE libs)

