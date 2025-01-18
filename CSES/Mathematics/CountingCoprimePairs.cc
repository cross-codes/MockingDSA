#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000000;

std::vector<u64> sieve() {
  std::vector<u64> unique{};

  bool primes[_ + 1];
  std::memset(primes, true, (_ + 1) * sizeof(bool));

  for (u64 i = 2; i <= _; i++) {
    if (primes[i]) {
      unique.push_back(i);
      for (u64 p = i * i; p <= _; p += i)
        primes[p] = false;
    }
  }

  return unique;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  auto vec = sieve();

  std::cout << vec.size() << "\n";

  return 0;
}
