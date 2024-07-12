#include <TinyRenderer/utils/Model.h>

#include <fstream>
#include <sstream>

namespace tinyrenderer
{

// ======================================================
Model::Model(std::string filePath)
{
  LoadOBJModel(filePath);
}

// ======================================================
bool Model::LoadOBJModel(std::string filePath)
{
  // Reset
  m_Faces.clear();
  m_Verts.clear();

  // Load file
  std::ifstream in;
  in.open(filePath, std::ifstream::in);
  if (in.fail()) return false;

  // Read file
  std::string line;
  while (!in.eof())
  {
    std::getline(in, line);
    // pretty funny shit
    // istringstream streams until whitespace, just keep using >> into variable
    // https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
    std::istringstream iss(line.c_str());
    std::string lineDef;
    iss >> lineDef;
    if (lineDef.compare("v") == 0)  // load vertices
    {
      glm::vec3 v;
      iss >> v.x;
      iss >> v.y;
      iss >> v.z;
      m_Verts.push_back(v);
    }
    else if (lineDef.compare("f") == 0)  // load faces
    {
      std::vector<int> f;
      int itrash, idx;
      char trash;
      // format:
      // f x/x/x x/x/x x/x/x/
      // the stream magic basically throws away everything
      // besides the first number in the "x/x/x" part
      // saves first 3 first numbers
      while (iss >> idx >> trash >> itrash >> trash >> itrash)
      {
        idx--;  // obj indices start at 1, make it so they can be indexed via 0
        f.push_back(idx);
      }
      m_Faces.push_back(f);
    }
  }
  return true;
}

// ======================================================
size_t Model::VertsSize() const
{
  return m_Verts.size();
}

// ======================================================
size_t Model::FacesSize() const
{
  return m_Faces.size();
}

// ======================================================
bool Model::IsLoaded() const
{
  return VertsSize() > 0 && FacesSize() > 0;
}

// ======================================================
glm::vec3 Model::Vertex(size_t i) const
{
  return m_Verts[i];
}

const std::vector<int>& Model::Face(size_t i) const
{
  return m_Faces[i];
}

}  // namespace tinyrenderer
