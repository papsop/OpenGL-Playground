#include <GLCore/Core/Application.h>
#include <GLCore/Core/Layer.h>
#include <GLCore/Utils/Log.h>

#include <iostream>
#include <memory>
int main(void)
{
  auto app = std::make_unique<GLCore::Application>();
  app->Run();
  return 0;
}
