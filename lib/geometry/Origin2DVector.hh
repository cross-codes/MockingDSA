#include <cmath>
#include <limits>
#include <string>

struct Vector2D {

  /*
   * Author: Akshaj Rao (cross-codes)
   */

public:
  int64_t x;
  int64_t y;

  Vector2D(int64_t x, int64_t y) : x(x), y(y) {}

  inline double norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  inline Vector2D add(const Vector2D &vector) const {
    return Vector2D(this->x + vector.x, this->y + vector.y);
  }

  inline Vector2D subtract(const Vector2D &vector) const {
    return Vector2D(this->x - vector.x, this->y - vector.y);
  }

  inline int64_t dot(const Vector2D &vector) const {
    return (this->x) * vector.x + (this->y) * vector.y;
  }

  inline int64_t cross(const Vector2D &vector) const {
    return (this->x) * vector.y - (this->y) * vector.x;
  }

  inline Vector2D perpendicularVector() const {
    return Vector2D(-(this->y), this->x);
  }

  inline double angle() const {
    if (this->x == 0)
      return this->y > 0 ? std::numeric_limits<double>::infinity()
                         : std::numeric_limits<double>::lowest();
    return __builtin_atan2(static_cast<double>(this->y),
                           static_cast<double>(this->x));
  }

  inline double angleBetween(const Vector2D &vector) const {
    int64_t dotProduct = (this->dot(vector));
    double normProduct = this->norm() * vector.norm();
    if (std::abs(normProduct) < 1e9)
      return (dotProduct > 0) ? std::numeric_limits<double>::infinity()
                              : std::numeric_limits<double>::lowest();
    return __builtin_acos(static_cast<double>(dotProduct) / normProduct);
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
