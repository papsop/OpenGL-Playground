#include <GLSandbox/Utils/SandWorld.h>
#include <GLCore/Utils/Log.h>

namespace GLSandbox {

SandWorld::SandWorld(size_t width, size_t height) : m_width(width), m_height(height), m_gen(m_rd())
{
  m_obstacleCell.Type = E_CellType::OBSTACLE;
  m_obstacleCell.Color = {0, 0, 0, 255};
  m_obstacleCell.Movement = E_CellMovement::NONE;

  // m_emptyCell is just default values

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

Cell& SandWorld::GetObstacleCell()
{
  return m_obstacleCell;
}

Cell& SandWorld::GetEmptyCell()
{
  return m_emptyCell;
}

void SandWorld::CommitChanges()
{
  std::sort(m_changes.begin(), m_changes.end(), [](auto& a, auto& b) { return a.first > b.first; });

  size_t collisionsStartIndex = 0;
  size_t lastDest = (m_changes.size() > 0) ? m_changes[0].first : UINT_MAX;

  for (size_t i = 0; i < m_changes.size(); i++) {
    auto& dest_i = m_changes[i].first;
    auto& source_i = m_changes[i].second;

    if (!GetCellValue(dest_i).IsType(E_CellType::EMPTY)) continue;

    if (lastDest != dest_i || i == m_changes.size() - 1) {
      size_t collisionsEndIndex = 0;
      // current collision sub-array is between (collisionsStartIndex, collisionsEndIndex), including endIndex
      // current destination is lastDest
      if (i == m_changes.size() - 1)
        collisionsEndIndex = i;  // include 'i', because it's the last element
      else
        collisionsEndIndex = i - 1;  // 'i' is already in the next sub-array, don't include

      std::uniform_int_distribution<size_t> distrib(collisionsStartIndex, collisionsEndIndex);
      size_t randomSource = distrib(m_gen);

      MoveCellImpl(lastDest, m_changes[randomSource].second);
      collisionsStartIndex = i;  // store for next collision sub-array
    }

    lastDest = dest_i;
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

void SandWorld::SetCell(size_t x, size_t y, const Cell& cell)
{
  if (!IsCellWithinBounds(x, y)) return;

  m_grid[GetCellIndex(x, y)] = cell;
}

void SandWorld::UpdateWorld()
{
  for (size_t y = 0; y < m_height; y++) {
    for (size_t x = 0; x < m_width; x++) {
      auto& cell = GetCellValue(x, y);

      // clang-format off
      if (cell.Movement & E_CellMovement::MOVE_BOTTOM && MoveCellBottomImpl(x, y, cell)) {}
      else if (cell.Movement & (E_CellMovement::MOVE_BOTTOM_LEFT  | E_CellMovement::MOVE_BOTTOM_LEFT) && MoveCellBottomSideImpl(x, y, cell)) {}
      else if (cell.Movement & (E_CellMovement::MOVE_LEFT | E_CellMovement::MOVE_RIGHT) && MoveCellSideImpl(x, y, cell)) {}
      // clang-format on
    }
  }
}

void SandWorld::MoveCell(size_t dest_x, size_t dest_y, size_t source_x, size_t source_y)
{
  m_changes.push_back({GetCellIndex(dest_x, dest_y), GetCellIndex(source_x, source_y)});
}

bool SandWorld::MoveCellBottomImpl(size_t x, size_t y, Cell cell)
{
  if (GetCellValue(x, y + 1).IsType(E_CellType::EMPTY)) {
    MoveCell(x, y + 1, x, y);
    return true;
  }
  return false;
}

bool SandWorld::MoveCellBottomSideImpl(size_t x, size_t y, Cell cell)
{
  std::uniform_int_distribution<size_t> distrib(0, 1);
  size_t rnd = distrib(m_gen);

  bool bottomLeft = GetCellValue(x - 1, y + 1).IsType(E_CellType::EMPTY);
  bool bottomRight = GetCellValue(x + 1, y + 1).IsType(E_CellType::EMPTY);

  if (bottomLeft && bottomRight) {
    bottomLeft = (rnd == 0);
    bottomRight = (rnd == 1);
  }

  if (bottomLeft)
    MoveCell(x - 1, y + 1, x, y);
  else if (bottomRight)
    MoveCell(x + 1, y + 1, x, y);

  return bottomLeft || bottomRight;
}

bool SandWorld::MoveCellSideImpl(size_t x, size_t y, Cell cell)
{
  std::uniform_int_distribution<size_t> distrib(0, 1);
  size_t rnd = distrib(m_gen);

  bool left = GetCellValue(x - 1, y).IsType(E_CellType::EMPTY);
  bool right = GetCellValue(x + 1, y).IsType(E_CellType::EMPTY);

  if (left && right) {
    left = (rnd == 0);
    right = (rnd == 1);
  }

  if (left)
    MoveCell(x - 1, y, x, y);
  else if (right)
    MoveCell(x + 1, y, x, y);

  return left || right;
}

void SandWorld::MoveCellImpl(size_t dest_index, size_t source_index)
{
  m_grid[dest_index] = m_grid[source_index];
  m_grid[source_index] = m_emptyCell;
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
