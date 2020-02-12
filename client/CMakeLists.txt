cmake_minimum_required(VERSION 3.9)
project(client)

file(GLOB_RECURSE CLIENT_SRC source/*.cpp)
list(REMOVE_ITEM CLIENT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/source/mainClient.cpp)

set(CLIENT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(client source/mainClient.cpp ${CLIENT_SRC})

# Create major target
add_library(myclient 
  STATIC
    ${CLIENT_SRC}
)

target_link_libraries(client
    PUBLIC
        interfaces
        proto_generated
        ${Protobuf_LIBRARIES}

)


message("==============================================")
message(${CMAKE_CURRENT_SOURCE_DIR}/../build/gen)
message("==============================================")


# Specify include directory
target_include_directories(client
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/../build/gen
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Specify include directory
target_include_directories(myclient
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/../build/gen
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      ${INTERFACE_INCLUDE}
)