#include <GLSandbox/Layers/SandLayer.h>
#include <GLCore/Core/Application.h>

#include <GLCore/Core/GLFWGlad.h>
#include <GLCore/Utils/Log.h>

#include <imgui.h>

namespace GLSandbox {

void SandLayer::OnAttach()
{
  REGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this, &SandLayer::OnSandboxCanvasMouseEvent);

  m_center = {0.0f, 0.0f};
  m_size = {10.0f, 10.0f};

  // initialize sand world and local cell types
  m_sandWorld = std::make_unique<SandWorld>(m_pixelsWidth, m_pixelsHeight);

  m_sandCell.Type = E_CellType::SAND;
  m_sandCell.Color = {205, 170, 109, 255};
  m_sandCell.Movement = E_CellMovement::MOVE_BOTTOM | E_CellMovement::MOVE_BOTTOM_LEFT | E_CellMovement::MOVE_BOTTOM_RIGHT;

  m_waterCell.Type = E_CellType::WATER;
  m_waterCell.Color = {14, 135, 204, 255};
  m_waterCell.Movement = E_CellMovement::MOVE_BOTTOM | E_CellMovement::MOVE_LEFT | E_CellMovement::MOVE_RIGHT;

  // Add static obstacle
  m_sandWorld->SetCell(48, 50, m_sandWorld->GetObstacleCell());
  m_sandWorld->SetCell(52, 50, m_sandWorld->GetObstacleCell());
  m_sandWorld->SetCell(48, 51, m_sandWorld->GetObstacleCell());
  m_sandWorld->SetCell(51, 51, m_sandWorld->GetObstacleCell());
  m_sandWorld->SetCell(49, 51, m_sandWorld->GetObstacleCell());
  m_sandWorld->SetCell(52, 51, m_sandWorld->GetObstacleCell());
}

void SandLayer::OnDetach()
{
  UNREGISTER_EVENT_CALLBACK(GLCore::E_SandboxCanvasMouseEvent, this);
}

void SandLayer::OnUpdate(GLCore::Timestep dt)
{
  // SandWorld update
  GL_TODO("Implement an actual update accumulator to fix weird update when on low FPS");
  m_updateAccumulator += dt.GetSeconds();
  if (m_updateAccumulator >= m_fixedUpdate) {
    UpdateSandWorld();
    m_updateAccumulator = 0.0f;

    // Rendering SandWorld to texture
    auto& grid = m_sandWorld->GetGrid();
    auto nextCell = grid.begin();

    unsigned char* nextPixel = &m_pixelsBuffer[0];
    for (int i = 0; i < m_pixelsWidth * m_pixelsHeight; i++) {
      if (nextCell == grid.end()) break;

      Cell cell = *nextCell;

      *nextPixel = cell.Color.r;
      ++nextPixel;
      *nextPixel = cell.Color.g;
      ++nextPixel;
      *nextPixel = cell.Color.b;
      ++nextPixel;
      *nextPixel = cell.Color.a;
      ++nextPixel;
      ++nextCell;
    }

    m_sandTexture.SetImageData(m_pixelsWidth, m_pixelsHeight, m_pixelsBuffer);
  }

  GLCore::Application::Instance().GetRenderer()->DrawQuad(m_center, m_size, &m_sandTexture);
}

void SandLayer::OnSandboxCanvasMouseEvent(const GLCore::E_SandboxCanvasMouseEvent& e)
{
  if (!IsEnabled()) return;

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

      for (int i = -10; i < 10; i++)
      {
        for (int j = -10; j < 10; j++)
        {
          Cell newCell;
          if(m_selectedState == 0) newCell = m_sandCell;
          else if(m_selectedState == 1) newCell = m_waterCell;

          m_sandWorld->SetCell(texPos.x + i, texPos.y + j, newCell);
        }
      }
    }

    // clang-format on
  }
}

void SandLayer::OnImGuiUpdate(GLCore::Timestep dt)
{
  if (!IsEnabled()) return;

  ImGui::Begin(GetName());
  ImGui::Text("Adding:");
  ImGui::SameLine();
  ImGui::RadioButton("Sand", &m_selectedState, 0);
  ImGui::SameLine();
  ImGui::RadioButton("Water", &m_selectedState, 1);

  ImGui::End();
}

void SandLayer::UpdateSandWorld()
{
  m_sandWorld->SetCell(49, 50, m_sandCell);
  m_sandWorld->SetCell(51, 50, m_sandCell);

  m_sandWorld->UpdateWorld();
  m_sandWorld->CommitChanges();
}

}  // namespace GLSandbox
