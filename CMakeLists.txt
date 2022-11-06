cmake_minimum_required(VERSION 3.21)
project(Caso_5_ED)

set(CMAKE_CXX_STANDARD 14)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
add_executable(curl-demo contenful.cpp)
target_link_libraries(curl-demo ${CURL_LIBRARIES})