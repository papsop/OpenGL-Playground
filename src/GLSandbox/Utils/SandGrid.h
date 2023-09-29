#pragma once
#include <vector>

namespace GLSandbox {
enum class E_CellType {
  NONE,
  OBSTACLE,
  SAND,
  WATER,
};

struct Cell {
  E_CellType Type = E_CellType::NONE;
};

class SandGrid {
 public:
  SandGrid(size_t width, size_t height);
  ~SandGrid();

  std::vector<Cell>& GetGrid();
  size_t GetWidth();
  size_t GetHeight();

 private:
  inline size_t GetCellIndex(size_t x, size_t y)
  {
    y = m_height - y - 1;  // indices normally start from [bottom,left] - swap to [top,left]
    return y * m_width + x;
  };

  Cell& GetCellValue(size_t x, size_t y);
  void SetCellType(size_t x, size_t y, E_CellType type);
  bool IsCellWithinBounds(size_t x, size_t y);
  bool IsCellEmpty(size_t x, size_t y);

  size_t m_width;
  size_t m_height;
  std::vector<Cell> m_grid;
};

}  // namespace GLSandbox
