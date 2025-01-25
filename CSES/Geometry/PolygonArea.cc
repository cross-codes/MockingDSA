#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cmath>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

struct OriginVector2D {
public:
  int64_t x;
  int64_t y;

  OriginVector2D(int64_t x, int64_t y) : x(x), y(y) {}

  inline double norm() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
  }

  inline OriginVector2D add(const OriginVector2D &vector) const {
    return OriginVector2D(this->x + vector.x, this->y + vector.y);
  }

  inline OriginVector2D subtract(const OriginVector2D &vector) const {
    return OriginVector2D(this->x - vector.x, this->y - vector.y);
  }

  inline int64_t dot(const OriginVector2D &vector) const {
    return (this->x) * vector.x + (this->y) * vector.y;
  }

  inline int64_t cross(const OriginVector2D &vector) const {
    return (this->x) * vector.y - (this->y) * vector.x;
  }

  inline OriginVector2D perpendicularVector() const {
    return OriginVector2D(-(this->y), this->x);
  }

  inline double angle() const {
    if (this->x == 0)
      return this->y > 0 ? std::numeric_limits<double>::infinity()
                         : std::numeric_limits<double>::lowest();
    return __builtin_atan2(static_cast<double>(this->y),
                           static_cast<double>(this->x));
  }

  inline double angleBetween(const OriginVector2D &vector) const {
    int64_t dotProduct = (this->dot(vector));
    double normProduct = this->norm() * vector.norm();
    if (std::abs(normProduct) < 1e9)
      return (dotProduct > 0) ? std::numeric_limits<double>::infinity()
                              : std::numeric_limits<double>::lowest();
    return __builtin_acos(static_cast<double>(dotProduct) / normProduct);
  }

  bool operator==(const OriginVector2D &vector) const {
    if (this == &vector)
      return true;
    return this->x == vector.x && this->y == vector.y;
  }

  inline std::string to_string() const {
    return std::to_string(this->x) + "i" + " + " + std::to_string(this->y) +
           "j";
  }
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  i64 x, y;
  std::cin >> n;

  std::cin >> x >> y;
  OriginVector2D first(x, y);
  OriginVector2D prev = first;

  i64 area = 0LL;
  for (u32 i = 1; i < n; i++) {
    std::cin >> x >> y;
    OriginVector2D vector(x, y);
    area += prev.cross(vector);
    prev = vector;
  }

  area += prev.cross(first);
  std::cout << std::abs(area) << "\n";

  return 0;
}
