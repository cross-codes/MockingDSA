#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 1000000;

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
