cmake_minimum_required(VERSION 3.21)
project(Caso_5_ED)

set(CMAKE_CXX_STANDARD 14)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
add_executable(curl-demo contentful/contenful.cpp ADT/BP_Tree.h ADT/BP_Node.h Main.cpp)
target_link_libraries(curl-demo ${CURL_LIBRARIES})