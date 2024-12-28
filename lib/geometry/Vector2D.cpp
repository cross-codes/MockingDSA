#include <cmath>
#include <limits>
#include <string>

class Vector2D {
public:
  int x;
  int y;

  Vector2D(int x, int y) : x(x), y(y) {}
  ~Vector2D() {}
  Vector2D(const Vector2D &vector) : x(vector.x), y(vector.y) {}

  inline double norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  inline Vector2D add(const Vector2D &vector) const {
    return Vector2D(this->x + vector.x, this->y + vector.y);
  }

  inline Vector2D subtract(const Vector2D &vector) const {
    return Vector2D(this->x - vector.x, this->y - vector.y);
  }

  inline long long dot(const Vector2D &vector) const {
    return static_cast<long long>(this->x) * vector.x +
           static_cast<long long>(this->y) * vector.y;
  }

  inline long long cross(const Vector2D &vector) const {
    return static_cast<long long>(this->x) * vector.y -
           static_cast<long long>(this->y) * vector.x;
  }

  inline Vector2D perpendicularVector() const {
    return Vector2D(-(this->y), this->x);
  }

  inline double angle() const {
    if (this->x == 0)
      return this->y > 0 ? std::numeric_limits<double>::infinity()
                         : std::numeric_limits<double>::lowest();
    return __builtin_atan2(this->y, this->x);
  }

  inline double angleBetween(const Vector2D &vector) const {
    double dotProduct = this->dot(vector);
    double normProduct = this->norm() * vector.norm();
    if (normProduct == 0)
      return (dotProduct > 0) ? std::numeric_limits<double>::infinity()
                              : std::numeric_limits<double>::lowest();
    return __builtin_acos(dotProduct / normProduct);
  }

  bool operator==(const Vector2D &vector) const {
    if (this == &vector)
      return true;
    return this->x == vector.x && this->y == vector.y;
  }

  inline std::string to_string() const {
    return std::to_string(this->x) + "i" + " + " + std::to_string(this->y) +
           "j";
  }
};