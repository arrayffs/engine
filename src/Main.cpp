#include <print>

#include "Engine.h"

int main()
{
  Engine* engine = Engine::inst();

  engine->init();
  
  while (engine->draw_frame());
  
  engine->shutdown();

  return 0;
}