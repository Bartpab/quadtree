include_directories(include)

find_package(SDL2 REQUIRED)

add_library(lib
  src/Container.cpp
  src/Events.cpp

  src/Application.cpp
  
  src/GraphicEngine.cpp

)

include_directories(lib PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (lib ${SDL2_LIBRARIES})
