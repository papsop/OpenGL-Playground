#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <random>

namespace GLSandbox {
enum class E_CellType {
  EMPTY,
  OBSTACLE,
  SAND,
  WATER,
};

// Add move_left and move_right
enum class E_CellMovement : unsigned { NONE = 0x0000, MOVE_BOTTOM = 0x0001, MOVE_BOTTOM_LEFT = 0x0010, MOVE_BOTTOM_RIGHT = 0x0100, MOVE_TOP = 0x1000 };

inline E_CellMovement operator|(E_CellMovement a, E_CellMovement b)
{
  return E_CellMovement(static_cast<int>(a) | static_cast<int>(b));
}

inline bool operator&(E_CellMovement a, E_CellMovement b)
{
  return static_cast<int>(a) & static_cast<int>(b);
}

struct Cell {
  E_CellType Type = E_CellType::EMPTY;
  E_CellMovement Movement = E_CellMovement::NONE;
  glm::ivec4 Color = {33, 33, 33, 255};

  bool IsType(E_CellType type)
  {
    return Type == type;
  }
};

class SandWorld {
 public:
  SandWorld(size_t width, size_t height);
  ~SandWorld();

  std::vector<Cell>& GetGrid();
  size_t GetWidth();
  size_t GetHeight();

  inline size_t GetCellIndex(size_t x, size_t y)
  {
    y = m_height - y - 1;  // indices normally start from [bottom,left] - swap to [top,left]
    return y * m_width + x;
  };

  inline glm::ivec2 GetCellPosition(size_t index)
  {
    return {index % m_width, index / m_height};
  }

  void MoveCell(size_t dest_x, size_t dest_y, size_t source_x, size_t source_y);
  void CommitChanges();

  Cell& GetCellValue(size_t x, size_t y);
  Cell& GetCellValue(size_t index);
  Cell& GetObstacleCell();
  Cell& GetEmptyCell();

  void SetCell(size_t x, size_t y, const Cell& cell);

  void UpdateWorld();

 private:
  bool MoveCellBottomImpl(size_t x, size_t y, Cell cell);
  bool MoveCellBottomLeftImpl(size_t x, size_t y, Cell cell);
  bool MoveCellBottomRightImpl(size_t x, size_t y, Cell cell);

  void MoveCellImpl(size_t dest_index, size_t source_index);
  bool IsCellWithinBounds(size_t x, size_t y);
  bool IsCellWithinBounds(size_t index);
  bool IsCellEmpty(size_t index);
  bool IsCellEmpty(size_t x, size_t y);

  std::random_device m_rd;
  std::mt19937 m_gen;

  size_t m_width;
  size_t m_height;

  size_t m_gridIndex = 0;

  Cell m_obstacleCell;  // bounds
  Cell m_emptyCell;

  std::vector<Cell> m_grid;

  // std::multimap<size_t, size_t> m_changes;  // destination; source in 1D index

  std::vector<std::pair<size_t, size_t>> m_changes;
};

}  // namespace GLSandbox
