#include <GLSandbox/Layers/SandLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>

namespace GLSandbox {

void SandLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &SandLayer::OnSandboxCanvasMouseEvent);

  m_center = {0.0f, 0.0f};
  m_size = {8.0f, 8.0f};

  m_sandGrid = std::make_unique<SandWorld>(100, 100);
  m_sandGrid->SetCellType(48, 50, E_CellType::OBSTACLE);
  m_sandGrid->SetCellType(52, 50, E_CellType::OBSTACLE);
  m_sandGrid->SetCellType(49, 51, E_CellType::OBSTACLE);
  m_sandGrid->SetCellType(48, 51, E_CellType::OBSTACLE);
  m_sandGrid->SetCellType(51, 51, E_CellType::OBSTACLE);
  m_sandGrid->SetCellType(52, 51, E_CellType::OBSTACLE);
}

void SandLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
}

void SandLayer::OnUpdate(GLCore::Timestep dt)
{
  auto& grid = m_sandGrid->GetGrid();

  if (m_currentCooldown > 0.0f) {
    m_currentCooldown -= dt.GetSeconds();
  }
  else {
    m_currentCooldown = m_updateCooldown;
    UpdateGridStates(grid);
    m_sandGrid->CommitChanges();
  }

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
  if (e.Type == GLCore::E_SandboxCanvasMouseEvent::LeftClickDown) {
    auto worldPos = GLCore::Application::Instance().GetMainCamera()->ScreenToWorld(e.Position);

    // clang-format off
    
    // AABB texture
    if (worldPos.x <= m_center.x + m_size.x / 2 &&
        worldPos.x >= m_center.x - m_size.x / 2 && 
        worldPos.y <= m_center.y + m_size.y / 2 &&
        worldPos.y >= m_center.y - m_size.y / 2) {
      
      glm::vec2 pos = (worldPos - m_center) / m_size;
      pos.y *= -1;
      pos += glm::vec2{ 0.5, 0.5 };
      
      glm::ivec2 texPos = { pos.x * m_pixelsWidth, pos.y * m_pixelsHeight };
      m_sandGrid->SetCellType(texPos.x, texPos.y, E_CellType::SAND);
    }

    // clang-format on
  }
}

glm::ivec4 SandLayer::GetColor(Cell cell)
{
  switch (cell.Type) {
    case E_CellType::EMPTY:
      return {33, 33, 33, 255};
    case E_CellType::OBSTACLE:
      return {0, 0, 0, 255};
    case E_CellType::SAND:
      return {205, 170, 109, 255};
    case E_CellType::WATER:
      return {14, 135, 204, 255};
    default:
      return {0, 0, 0, 255};
  }
}

void SandLayer::UpdateGridStates(std::vector<Cell>& grid)
{
  m_sandGrid->SetCellType(49, 50, E_CellType::SAND);
  m_sandGrid->SetCellType(51, 50, E_CellType::SAND);

  for (size_t i = 0; i < m_pixelsHeight; i++) {
    for (size_t j = 0; j < m_pixelsWidth; j++) {
      auto& currentCell = m_sandGrid->GetCellValue(j, i);

      if (currentCell.IsType(E_CellType::SAND)) {
        bool bottom = m_sandGrid->GetCellValue(j, i + 1).IsType(E_CellType::EMPTY);
        bool bottomLeft = m_sandGrid->GetCellValue(j - 1, i + 1).IsType(E_CellType::EMPTY);
        bool bottomRight = m_sandGrid->GetCellValue(j + 1, i + 1).IsType(E_CellType::EMPTY);

        if (bottom)
          m_sandGrid->MoveCell(j, i + 1, j, i);
        else if (bottomLeft)
          m_sandGrid->MoveCell(j - 1, i + 1, j, i);
        else if (bottomRight)
          m_sandGrid->MoveCell(j + 1, i + 1, j, i);
      }
    }
  }
}

}  // namespace GLSandbox
