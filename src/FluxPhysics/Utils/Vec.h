#pragma once
#include <type_traits>
#include <iostream>

namespace flux {

template <typename VecType>
class Vec3 {
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

  void normalize()
  {
    VecType vlength = length();
    x /= vlength;
    y /= vlength;
    z /= vlength;
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

typedef Vec3<float> Vec3f;
}  // namespace flux
