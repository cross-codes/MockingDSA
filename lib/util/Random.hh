#include <chrono>
#include <cstdint>

struct Random {
private:
  Random();
  inline static int64_t seed =
      std::chrono::steady_clock::now().time_since_epoch().count() ^
      8682522807148012ULL;

  static int next(unsigned int bits) {
    seed = seed * 0x5DEECE66DLL + 0xBLL & 0xFFFFFFFFFFFFLL;
    return static_cast<int>(seed >> (48 - bits));
  }

public:
  static int nextInt() { return next(32); }

  static int nextInt(int bound) {
    int r = next(31);
    int m = bound - 1;
    if ((bound & m) == 0)
      r = static_cast<int>(bound * static_cast<int64_t>(r) >> 31);
    else
      for (int u = r; u - (r = u % bound) + m < 0; u = next(31))
        ;
    return r;
  }

  static int64_t next64() {
    return static_cast<int64_t>(next(32)) << 32 | next(32);
  }

  static double nextDouble() {
    return (static_cast<int64_t>(next(26)) << 27 | next(27)) * 0x1.0p-53;
  }
};
