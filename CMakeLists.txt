cmake_minimum_required(VERSION 3.16)
project(multicast_test)
set(CMAKE_CXX_STANDARD 17)

find_package (Threads REQUIRED)

#Include KCP
include(ExternalProject)
ExternalProject_Add(kissnet_source
        GIT_REPOSITORY https://github.com/andersc/kissnet.git
        GIT_SUBMODULES ""
        UPDATE_COMMAND ""
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/kissnet
        BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/kissnet
        GIT_PROGRESS 1
        BUILD_COMMAND ""
        STEP_TARGETS build
        EXCLUDE_FROM_ALL TRUE
        INSTALL_COMMAND ""
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kissnet/)

add_executable(multicast_send multicast_send.cpp)
add_dependencies(multicast_send kissnet_source)
target_link_libraries(multicast_send Threads::Threads)

add_executable(multicast_receive multicast_receive.cpp)
add_dependencies(multicast_receive kissnet_source)
target_link_libraries(multicast_receive Threads::Threads)
