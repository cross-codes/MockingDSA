#include <cstdint>
#include <cstdlib>

class Solution
{
private:
  auto pow(double x, int64_t absn) -> double
  {
    if (absn == 0)
      return 1.0;

    double u = pow(x, absn >> 1);
    u        = u * u;

    if (absn & 1)
      u = u * x;

    return u;
  }

public:
  double myPow(double x, int n)
  {
    double res = pow(x, std::abs(static_cast<int64_t>(n)));
    if (n < 0)
      return 1.0 / res;

    return res;
  }
};
