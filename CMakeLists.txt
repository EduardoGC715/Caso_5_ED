cmake_minimum_required(VERSION 3.21)
project(Caso_5_ED)

set(CMAKE_CXX_STANDARD 14)
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
add_executable(curl-demo ADT/BP_Tree.h ADT/BP_Node.h Main.cpp contentful/contentful.h contentful/contentful_functions.h Output/GUI.h)
target_link_libraries(curl-demo ${CURL_LIBRARIES})