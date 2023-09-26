#include <GLCore/Core/Application.h>
#include <GLSandbox/Layers/DrawingLayer.h>
#include <GLSandbox/Layers/SandLayer.h>

#include <iostream>
#include <memory>
int main(void)
{
  auto app = std::make_unique<GLCore::Application>();
  app->PushLayer(new GLSandbox::DrawingLayer());
  app->PushLayer(new GLSandbox::SandLayer());
  app->Run();

  return 0;
}
