#include <GLSandbox/Utils/SandWorld.h>
#include <GLCore/Utils/Log.h>

namespace GLSandbox {

SandWorld::SandWorld(size_t width, size_t height) : m_width(width), m_height(height), m_gen(m_rd())
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

std::vector<Cell>& SandWorld::GetGrid()
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
  std::sort(m_changes.begin(), m_changes.end(), [](auto& a, auto& b) { return a.first > b.first; });

  size_t lastCollisionI = 0;
  size_t lastDest = (m_changes.size() > 0) ? m_changes[0].first : UINT_MAX;

  for (size_t i = 0; i < m_changes.size(); i++) {
    auto& dest_i = m_changes[i].first;
    auto& source_i = m_changes[i].second;

    if (!GetCellValue(dest_i).IsType(E_CellType::EMPTY)) continue;

    if (lastDest != dest_i || i == m_changes.size() - 1) {
      // current collision is between (lastCollisionI, i-1)
      // current destination is lastDest

      GL_TODO("Refactor this");
      if (i == m_changes.size() - 1) {
        i++;
      }
      std::uniform_int_distribution<size_t> distrib(lastCollisionI, i - 1);
      size_t randomSource = distrib(m_gen);

      MoveCellImpl(lastDest, m_changes[randomSource].second);
      lastCollisionI = i;
    }

    lastDest = dest_i;

    //     std::uniform_int_distribution<size_t> distrib(lastCollisionI, i - 1);
    //     size_t randomSource = distrib(m_gen);
  }
  m_changes.clear();
}

Cell& SandWorld::GetCellValue(size_t x, size_t y)
{
  if (!IsCellWithinBounds(x, y)) return m_obstacleCell;

  return GetCellValue(GetCellIndex(x, y));
}

Cell& SandWorld::GetCellValue(size_t index)
{
  if (!IsCellWithinBounds(index)) return m_obstacleCell;

  return m_grid[index];
}

void SandWorld::SetCellType(size_t x, size_t y, E_CellType type)
{
  if (!IsCellWithinBounds(x, y)) return;

  m_grid[GetCellIndex(x, y)].Type = type;
}

void SandWorld::MoveCell(size_t dest_x, size_t dest_y, size_t source_x, size_t source_y)
{
  m_changes.push_back({GetCellIndex(dest_x, dest_y), GetCellIndex(source_x, source_y)});
}

void SandWorld::MoveCellImpl(size_t dest_index, size_t source_index)
{
  m_grid[dest_index] = m_grid[source_index];
  m_grid[source_index].Type = E_CellType::EMPTY;
}

bool SandWorld::IsCellWithinBounds(size_t x, size_t y)
{
  return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool SandWorld::IsCellWithinBounds(size_t index)
{
  return index >= 0 && index < m_width * m_height;
}

bool SandWorld::IsCellEmpty(size_t x, size_t y)
{
  return IsCellWithinBounds(x, y) && GetCellValue(x, y).IsType(E_CellType::EMPTY);
}

bool SandWorld::IsCellEmpty(size_t index)
{
  return IsCellWithinBounds(index) && GetCellValue(index).IsType(E_CellType::EMPTY);
}

}  // namespace GLSandbox
