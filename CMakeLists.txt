cmake_minimum_required(VERSION 3.9)

set(BUILD_TESTING OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(INTERFACE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/include)

add_subdirectory(client)
add_subdirectory(client2)
add_subdirectory(interfaces)
add_subdirectory(gen)
add_subdirectory(server)