#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <random>

namespace GLSandbox {
enum class E_CellType {
  EMPTY,
  OBSTACLE,
  SAND,
  WATER,
};

struct Cell {
  E_CellType Type = E_CellType::EMPTY;

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

  void SetCellType(size_t x, size_t y, E_CellType type);

 private:
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

  std::vector<Cell> m_grid;

  // std::multimap<size_t, size_t> m_changes;  // destination; source in 1D index

  std::vector<std::pair<size_t, size_t>> m_changes;
};

}  // namespace GLSandbox
