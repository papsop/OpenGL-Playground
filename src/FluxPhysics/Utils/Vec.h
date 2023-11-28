#pragma once
#include <type_traits>
#include <iostream>

namespace flux
{
// ======================================================
template <typename VecType>
class Vec3
{
  // Vector data
 public:
  VecType x;
  VecType y;

  VecType z;

 private:
  VecType pad;

  // Operations
 public:
  Vec3() : Vec3(0, 0, 0)
  {
  }
  Vec3(VecType x, VecType y, VecType z) : x(x), y(y), z(z), pad(0){};
  Vec3(VecType n) : x(n), y(n), z(n), pad(0)
  {
  }

  // Operators
  Vec3 operator-() const
  {
    return {-x, -y, -z};
  }
  Vec3 operator*(const VecType val) const
  {
    return {x * val, y * val, z * val};
  }

  Vec3 operator/(const VecType val) const
  {
    return (*this) * (static_cast<VecType>(1) / val);
  }

  void operator*=(const VecType val)
  {
    x *= val;
    y *= val;
    z *= val;
  }

  void operator/=(const VecType val)
  {
    x /= val;
    y /= val;
    z /= val;
  }

  Vec3 operator+(const Vec3& other) const
  {
    return {other.x + x, other.y + y, other.z + z};
  }

  void operator+=(const Vec3& other)
  {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  Vec3 operator-(const Vec3& other) const
  {
    return *this + (-other);
  }

  void operator-=(const Vec3& other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
  {
    os << "[" << v.x << "," << v.y << "," << v.z << "]";
    return os;
  }

  // let's ignore component product for now, will add later if needed

  // a.dot(b) = |a|*|b|*cos(phi)
  VecType dot(const Vec3& other) const
  {
    return x * other.x + y * other.y + z * other.z;
  }

  // |a.cross(b)| = |a|*|b|*sin(phi)
  Vec3 cross(const Vec3& other) const
  {
    return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
  }

  // Helper functions
  void invert()
  {
    *this = -(*this);
  }

  Vec3 normalize()
  {
    VecType vlength = length();
    x /= vlength;
    y /= vlength;
    z /= vlength;
    return *this;
  }

  void clear()
  {
    x = 0;
    y = 0;
    z = 0;
  }

  VecType length()
  {
    return sqrt(lengthSquared());
  }

  VecType lengthSquared()
  {
    return x * x + y * y + z * z;
  }
};

// ======================================================
template <typename VecType>
class Vec4
{
  // Vector data
 public:
  VecType r;
  VecType g;
  VecType b;
  VecType a;

  // Operations
 public:
  Vec4() : Vec4(0, 0, 0, 0)
  {
  }
  Vec4(VecType r, VecType g, VecType b, VecType a) : r(r), g(g), b(b), a(a){};
  Vec4(VecType n) : r(n), g(n), b(n), a(n)
  {
  }
};

// ======================================================
typedef Vec3<float> Vec3f;
typedef Vec4<float> Vec4f;
}  // namespace flux
