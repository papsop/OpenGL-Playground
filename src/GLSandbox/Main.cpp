#include <GLCore/Core/Application.h>

#include <GLSandbox/Layers/DrawingLayer.h>
#include <GLSandbox/Layers/SandLayer.h>
#include <GLSandbox/Layers/GLTFViewerLayer.h>
#include <GLSandbox/Layers/PhysicsLayer.h>
#include <GLSandbox/Layers/TinyRendererLayer.h>

#include <iostream>
#include <memory>

int main(void)
{
  auto app = std::make_unique<GLCore::Application>();
  app->PushLayer(new GLSandbox::DrawingLayer(false));
  app->PushLayer(new GLSandbox::SandLayer(false));
  app->PushLayer(new GLSandbox::GLTFViewerLayer(false));
  app->PushLayer(new GLSandbox::PhysicsLayer(false));
  app->PushLayer(new GLSandbox::TinyRendererLayer(true));
  app->Run();

  return 0;
}
