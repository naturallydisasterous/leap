cmake_minimum_required(VERSION 3.5.1)

# project name
set(NAME "leap")
project(${NAME})

set(EXEC ${NAME})

# c++14 standard
set(CMAKE_CXX_STANDARD 14)

if(UNIX AND NOT APPLE)
  message("Building Project on Linux.")
else()
  message( FATAL_ERROR "Leap can only be built on Linux.")
endif(UNIX AND NOT APPLE)

include_directories(includes)

set(LIBS ola)

file(GLOB SOURCE
  "src/*.h"
  "src/*.cpp"
  "src/*/*.h"
  "src/*/*.cpp"
)

add_executable(${NAME} ${SOURCE})
target_link_libraries(${NAME} ${LIBS})
