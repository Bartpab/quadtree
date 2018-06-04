#include "Quanta.h"

int main(int argc, char const *argv[]) {
  auto builder = ApplicationBuilder();

  builder.addEngine(new GraphicEngineAllocator());

  auto app = builder.construct();

  app->init();
  app->start();

  delete app;
  return 0;
}
