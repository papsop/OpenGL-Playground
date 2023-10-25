#include <GLSandbox/Utils/Model.h>
#include <GLCore/Utils/Log.h>

namespace GLSandbox {

Model::Model()
{
}

void Model::SetPosition(glm::vec3 position)
{
  if (position == m_Position) return;
  m_Position = position;
  m_IsTransformDirty = true;
}

void Model::SetRotation(glm::vec3 rotation)
{
  if (rotation == m_Rotation) return;
  m_Rotation = rotation;
  m_IsTransformDirty = true;
}

void Model::SetScale(glm::vec3 scale)
{
  if (scale == m_Scale) return;
  m_Scale = scale;
  m_IsTransformDirty = true;
}

void Model::Draw()
{
}

glm::mat4 Model::GetModelTransformMatrix()
{
  if (m_IsTransformDirty) {
    // clang-format off
    glm::mat4 scale = glm::mat4({m_Scale.x, 0, 0, 0},
                                {0, m_Scale.y, 0, 0},
                                {0, 0, m_Scale.z, 0},
                                {0, 0, 0, 1});

    glm::mat4 translate = glm::mat4({1, 0, 0, m_Position.x},
                                    {0, 1, 0, m_Position.y},
                                    {0, 0, 1, m_Position.z},
                                    {0, 0, 0, 1});
    // clang-format on
    GL_TODO("Add rotation");

    m_Transform = translate * scale;
    m_IsTransformDirty = false;
  }

  return m_Transform;
}

}  // namespace GLSandbox
