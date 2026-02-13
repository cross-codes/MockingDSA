#include <cmath>
#include <cstdint>
#include <string>

struct Origin2DVector {
 public:
  std::int64_t x;
  std::int64_t y;

  Origin2DVector(std::int64_t x, std::int64_t y) : x(x), y(y) {}

  inline double norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  inline Origin2DVector add(const Origin2DVector& vector) const {
    return Origin2DVector(this->x + vector.x, this->y + vector.y);
  }

  inline Origin2DVector subtract(const Origin2DVector& vector) const {
    return Origin2DVector(this->x - vector.x, this->y - vector.y);
  }

  inline std::int64_t dot(const Origin2DVector& vector) const {
    return (this->x) * vector.x + (this->y) * vector.y;
  }

  inline std::int64_t cross(const Origin2DVector& vector) const {
    return (this->x) * vector.y - (this->y) * vector.x;
  }

  inline Origin2DVector perpendicular_vector() const {
    return Origin2DVector(-(this->y), this->x);
  }

  inline double angle() const {
    if (this->x == 0)
      return this->y > 0 ? std::numeric_limits<double>::infinity()
                         : std::numeric_limits<double>::lowest();
    return __builtin_atan2(static_cast<double>(this->y),
                           static_cast<double>(this->x));
  }

  inline double angle_between(const Origin2DVector& vector) const {
    std::int64_t dotProduct = (this->dot(vector));
    double normProduct      = this->norm() * vector.norm();
    if (std::abs(normProduct) < 1e9)
      return (dotProduct > 0) ? std::numeric_limits<double>::infinity()
                              : std::numeric_limits<double>::lowest();
    return __builtin_acos(static_cast<double>(dotProduct) / normProduct);
  }

  bool operator==(const Origin2DVector& vector) const {
    if (this == &vector)
      return true;
    return this->x == vector.x && this->y == vector.y;
  }

  inline std::string to_string() const {
    return std::to_string(this->x) + "i" + " + " + std::to_string(this->y) +
           "j";
  }
};
