#include <GLCore/Utils/PerspectiveCamera.h>

namespace GLCore {
glm::vec2 PerspectiveCamera::ScreenToWorld(glm::vec2 pos)
{
  return {0, 0};
}

void PerspectiveCamera::RecalculateProjectionMatrix()
{
}
}  // namespace GLCore
