find_package(SDL2 REQUIRED)

include_directories(
  include
  ${CMAKE_SOURCE_DIR}/lib/include
  ${SDL2_INCLUDE_DIRS}
)

add_executable(quadtree
  src/main.cpp
)

target_link_libraries (quadtree LINK_PUBLIC libquanta)
