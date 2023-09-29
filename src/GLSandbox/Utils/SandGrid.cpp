#include <GLSandbox/Utils/SandGrid.h>
#include <GLCore/Utils/Log.h>

namespace GLSandbox {

SandGrid::SandGrid(size_t width, size_t height) : m_width(width), m_height(height)
{
  m_grid = std::vector<Cell>(m_width * m_height);

  // grid indices:
  // 0,0    w,0
  //  ______
  // |      |
  // |      |
  // |______|
  // 0,h    w,h

  for (int i = 0; i < m_height; i++) {
    SetCellType(i, i, E_CellType::SAND);
    SetCellType(i, 0, E_CellType::WATER);
    SetCellType(0, i, E_CellType::OBSTACLE);
  }
}

SandGrid::~SandGrid()
{
  m_grid.clear();
}

std::vector<GLSandbox::Cell>& SandGrid::GetGrid()
{
  return m_grid;
}

size_t SandGrid::GetWidth()
{
  return m_width;
}

size_t SandGrid::GetHeight()
{
  return m_height;
}

Cell& SandGrid::GetCellValue(size_t x, size_t y)
{
  return m_grid[GetCellIndex(x, y)];
}

void SandGrid::SetCellType(size_t x, size_t y, E_CellType type)
{
  GL_ASSERT(IsCellWithinBounds(x, y), "Trying to set a cell outside of bounds");
  m_grid[GetCellIndex(x, y)].Type = type;
}

bool SandGrid::IsCellWithinBounds(size_t x, size_t y)
{
  return x >= 0 && x < m_width && y >= 0 && y < m_height;
}
bool SandGrid::IsCellEmpty(size_t x, size_t y)
{
  return IsCellWithinBounds(x, y) && GetCellValue(x, y).Type == E_CellType::NONE;
}

}  // namespace GLSandbox
