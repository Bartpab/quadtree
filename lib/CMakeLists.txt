include_directories(include)

find_package(SDL2 REQUIRED)

add_library(libquanta
  src/Container.cpp
  src/Events.cpp

  src/Application.cpp
    src/ApplicationBuilder.cpp
      src/ConstructEngineParameters.cpp
    src/ApplicationAccessors.cpp


  src/GraphicEngine.cpp
  src/EventEngine.cpp
)

include_directories(libquanta PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (libquanta ${SDL2_LIBRARIES})
