#include <GLCore/Core/Layer.h>

namespace GLCore {

void I_Layer::SetEnabled(bool val) { m_enabled = val; }

bool I_Layer::IsEnabled() const { return m_enabled; }

}  // namespace GLCore
