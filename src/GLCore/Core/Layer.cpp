#include <GLCore/Core/Layer.h>

namespace GLCore {

void I_Layer::SetEnabled(bool val)
{
  m_enabled = val;
}

bool I_Layer::IsEnabled() const
{
  return m_enabled;
}

bool I_Layer::IsLocked() const
{
  return m_isLocked;
}

bool I_Layer::ShouldUpdate() const
{
  return IsEnabled() || IsLocked();
}

}  // namespace GLCore
