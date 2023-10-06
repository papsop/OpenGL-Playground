#include <GLSandbox/Utils/SandWorld.h>
#include <GLCore/Utils/Log.h>

namespace GLSandbox {

SandWorld::SandWorld(size_t width, size_t height) : m_width(width), m_height(height)

{
  m_obstacleCell.Type = E_CellType::OBSTACLE;

  m_grid = std::vector<Cell>(m_width * m_height);

  // grid indices:
  // 0,0    w,0
  //  ______
  // |      |
  // |      |
  // |______|
  // 0,h    w,h

  //   for (int i = 0; i < m_height; i++) {
  //     SetCellType(i, i, E_CellType::SAND);
  //     SetCellType(i, 0, E_CellType::WATER);
  //     SetCellType(0, i, E_CellType::OBSTACLE);
  //   }
  // SwapGrids();
}

SandWorld::~SandWorld()
{
  m_grid.clear();
}

std::vector<GLSandbox::Cell>& SandWorld::GetGrid()
{
  return m_grid;
}

size_t SandWorld::GetWidth()
{
  return m_width;
}

size_t SandWorld::GetHeight()
{
  return m_height;
}

void SandWorld::CommitChanges()
{
  // TODO: just a quick impl, Left cell always wins, because it's change is first
  // make it more random
  size_t lastDest = UINT_MAX;
  for (auto& change : m_changes) {
    if (!m_grid[change.first].IsType(E_CellType::EMPTY)) continue;  // skip already taken cell, f.e. by mouse clicking

    if (lastDest != change.first) {
      m_grid[change.first] = m_grid[change.second];
      m_grid[change.second].Type = E_CellType::EMPTY;
    }
    lastDest = change.first;
  }
  m_changes.clear();
}

Cell& SandWorld::GetCellValue(size_t x, size_t y)
{
  if (!IsCellWithinBounds(x, y)) return m_obstacleCell;

  return m_grid[GetCellIndex(x, y)];
}

void SandWorld::SetCellType(size_t x, size_t y, E_CellType type)
{
  if (!IsCellWithinBounds(x, y)) return;

  m_grid[GetCellIndex(x, y)].Type = type;
}

void SandWorld::MoveCell(size_t dest_x, size_t dest_y, size_t source_x, size_t source_y)
{
  m_changes.insert({GetCellIndex(dest_x, dest_y), GetCellIndex(source_x, source_y)});
}

bool SandWorld::IsCellWithinBounds(size_t x, size_t y)
{
  return x >= 0 && x < m_width && y >= 0 && y < m_height;
}
bool SandWorld::IsCellEmpty(size_t x, size_t y)
{
  return IsCellWithinBounds(x, y) && GetCellValue(x, y).Type == E_CellType::EMPTY;
}

}  // namespace GLSandbox
