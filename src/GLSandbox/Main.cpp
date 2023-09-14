#include <GLCore/Core/Application.h>

#include <GLSandbox/Layers/TestLayer.h>

#include <iostream>
#include <memory>
int main(void)
{
  auto app = std::make_unique<GLCore::Application>();
  app->PushLayer(new GLSandbox::TestLayer());
  app->Run();

  return 0;
}
