#include <GLCore/Core/Application.h>

#include <GLSandbox/Layers/DrawingLayer.h>
#include <GLSandbox/Layers/SandLayer.h>
#include <GLSandbox/Layers/GLTFViewerLayer.h>
#include <GLSandbox/Layers/PhysicsLayer.h>

#include <FluxPhysics/Utils/Vec.h>

#include <iostream>
#include <memory>

int main(void)
{
  flux::Vec3f vec1(2, 3, 4);
  flux::Vec3f vec2(5, 6, 7);
  std::cout << vec1.cross(vec2);

  auto app = std::make_unique<GLCore::Application>();
  app->PushLayer(new GLSandbox::DrawingLayer());
  app->PushLayer(new GLSandbox::SandLayer());
  app->PushLayer(new GLSandbox::GLTFViewerLayer());
  app->PushLayer(new GLSandbox::PhysicsLayer());
  app->Run();

  return 0;
}
