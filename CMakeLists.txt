cmake_minimum_required(VERSION 3.16)
project(multicast_test)
set(CMAKE_CXX_STANDARD 17)

find_package (Threads REQUIRED)

# Where we get kissnet from
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

# Where we get the header file from
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/kissnet/)

# Build multicast_send
add_executable(multicast_send multicast_send.cpp)
add_dependencies(multicast_send kissnet_source)
target_link_libraries(multicast_send Threads::Threads)

# Build multicast_receive
add_executable(multicast_receive multicast_receive.cpp)
add_dependencies(multicast_receive kissnet_source)
target_link_libraries(multicast_receive Threads::Threads)
