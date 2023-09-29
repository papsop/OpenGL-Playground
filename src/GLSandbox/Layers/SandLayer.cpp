#include <GLSandbox/Layers/SandLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>

namespace GLSandbox {

void SandLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &SandLayer::OnSandboxCanvasMouseEvent);

  m_center = {0.0f, 0.0f};
  m_size = {8.0f, 8.0f};

  m_sandGrid = std::make_unique<SandGrid>(100, 100);
}

void SandLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
}

void SandLayer::OnUpdate(GLCore::Timestep dt)
{
  auto& grid = m_sandGrid->GetGrid();

  auto nextCell = grid.begin();

  unsigned char* nextPixel = &m_pixelsBuffer[0];
  for (int i = 0; i < m_pixelsWidth * m_pixelsHeight; i++) {
    if (nextCell == grid.end()) break;

    auto color = GetColor(*nextCell);

    *nextPixel = color.r;
    ++nextPixel;
    *nextPixel = color.g;
    ++nextPixel;
    *nextPixel = color.b;
    ++nextPixel;
    *nextPixel = color.a;
    ++nextPixel;
    ++nextCell;
  }

  m_sandTexture.SetImageData(m_pixelsWidth, m_pixelsHeight, m_pixelsBuffer);
  GLCore::Application::Instance().GetRenderer()->DrawQuad(m_center, m_size, &m_sandTexture);
}

void SandLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
}

glm::ivec4 SandLayer::GetColor(Cell cell)
{
  switch (cell.Type) {
    case E_CellType::NONE:
      return {33, 33, 33, 255};
    case E_CellType::OBSTACLE:
      return {0, 0, 0, 255};
    case E_CellType::SAND:
      return {205, 170, 109, 255};
    case E_CellType::WATER:
      return {14, 135, 204, 255};
  }
}

}  // namespace GLSandbox
