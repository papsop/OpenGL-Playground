#include <GLCore/Core/Application.h>

#include <GLSandbox/Layers/DrawingLayer.h>

#include <iostream>
#include <memory>
int main(void)
{
  auto app = std::make_unique<GLCore::Application>();
  app->PushLayer(new GLSandbox::DrawingLayer());
  app->Run();

  return 0;
}
