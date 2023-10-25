#include <GLSandbox/Utils/Model.h>
#include <GLCore/Utils/Log.h>
#include <glm/ext/matrix_transform.hpp>

namespace GLSandbox {

Model::Model()
{
  m_IsTransformDirty = true;
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

glm::vec3 Model::GetPosition()
{
  return m_Position;
}

glm::vec3 Model::GetScale()
{
  return m_Scale;
}

void Model::Draw()
{
}

glm::mat4 Model::GetModelTransformMatrix()
{
  if (m_IsTransformDirty) {
    // clang-format off
    glm::mat4 scale = glm::scale(glm::mat4{1.0f}, m_Scale);
    glm::mat4 translate = glm::translate(glm::mat4{1.0f}, m_Position);

    // clang-format on
    GL_TODO("Add rotation");

    m_Transform = translate * scale;
    m_IsTransformDirty = false;
  }

  return m_Transform;
}

}  // namespace GLSandbox
