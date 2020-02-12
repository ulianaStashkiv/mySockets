cmake_minimum_required(VERSION 3.9)
project(server)

find_package(Threads)

file(GLOB_RECURSE SERVER_SRC source/*.cpp)
list(REMOVE_ITEM SERVER_SRC ${CMAKE_CURRENT_SOURCE_DIR}/source/mainServer.cpp)

set(SERVER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(server source/mainServer.cpp ${SERVER_SRC})

target_link_libraries(server
    PUBLIC
        interfaces
        myclient
        ${CMAKE_THREAD_LIBS_INIT}
        proto_generated
)

# Specify include directory
target_include_directories(server
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)