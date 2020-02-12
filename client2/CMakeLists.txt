cmake_minimum_required(VERSION 3.9)

set(CXX_STANDARD_REQUIRED 14)
file(GLOB_RECURSE CLIENT2_SRC ../client/source/*.cpp)
list(REMOVE_ITEM CLIENT2_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../client/source/mainClient.cpp)

set(CLIENT2_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../client/include)

add_executable(proc2 source/mainClient2.cpp ${CLIENT2_SRC})

target_link_libraries(proc2
    PUBLIC
        interfaces
        proto_generated
        ${Protobuf_LIBRARIES}

)

target_include_directories(proc2
  PRIVATE
    ${CLIENT2_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/../build/gen

)