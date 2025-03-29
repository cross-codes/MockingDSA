#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _CountingDivisors {

struct FixedDensePrime {
  /*
   * Author: github.com/cross-codes
   */

 private:
  constexpr inline static int N = 1000001;
  std::array<int, N> minima_, powers_;
  std::bitset<N> parity_, squareFree_;

 public:
  std::vector<int> primes_;

  explicit FixedDensePrime() : minima_{}, powers_{} {
    for (int i = 2; i < (N + 1) >> 1; i++) {
      int minimum, power;
      if (minima_[i] == 0) {
        minimum = i;
        power   = 1;
        parity_.set(i, true);
        squareFree_.set(i, true);
        primes_.push_back(i);
      } else {
        minimum = minima_[i];
        power   = powers_[i];
      }

      for (int e : primes_) {
        int index{e * i};
        if (index < N) {
          minima_[index] = e;
          parity_.set(index, !parity_[i]);
          if (e == minimum) {
            powers_[index] = power + 1;
            break;
          } else {
            powers_[index] = 1;
            squareFree_.set(index, squareFree_[i]);
          }
        } else
          break;
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2) {
      if (minima_[i] == 0) {
        parity_.set(i, true);
        squareFree_.set(i, true);
      }
    }
  }

  auto isSquareFree(int n) -> bool { return squareFree_[n]; }
  auto getParity(int n) -> bool { return parity_[n]; }

  auto totient(int n) -> int {
    int result{1};
    while (minima_[n] != 0) {
      int factor{1};
      for (int i = 1; i < powers_[n]; i++)
        factor *= minima_[n];
      result *= factor * (minima_[n] - 1);
      n /= factor * minima_[n];
    }

    if (n != 1)
      result *= n - 1;

    return result;
  }

  void forPrimeFactors(int n, std::function<void(const int&)> consume) {
    while (minima_[n] != 0) {
      consume(minima_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(n);
  }

  void forPowers(int n, std::function<void(const int&)> consume) {
    while (minima_[n] != 0) {
      consume(powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(1);
  }

  void forPrimeFactorsAndPowers(
      int n,
      std::function<void(const int&, const int&)> biConsume) {
    while (minima_[n] != 0) {
      biConsume(minima_[n], powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      biConsume(n, 1);
  }

  void forFactors(int n,
                  bool include1,
                  bool includeN,
                  std::function<void(const int&)> consume) {
    if (n == 1) {
      if (include1 && includeN)
        consume(1);
    } else {
      if (include1)
        consume(1);

      std::vector<int> primeFactors{}, powers{};

      forPrimeFactorsAndPowers(n, [&primeFactors, &powers](int a, int b) {
        primeFactors.push_back(a), powers.push_back(b);
      });

      std::vector<int> factors = primeFactors;
      std::unique_ptr<int[]> currentPowers(new int[factors.size()]);
      std::ranges::fill(currentPowers.get(),
                        currentPowers.get() + factors.size(), 1);

      int index{};
      while (true) {
        if (currentPowers[index] > powers[index])
          index++;
        else if (factors[index] == n) {
          if (includeN)
            consume(n);
          break;
        } else {
          consume(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * primeFactors[i];

          std::ranges::fill(currentPowers.get(), currentPowers.get() + index,
                            1);

          currentPowers[index]++;
          index = 0;
        }
      }
    }
  }
};

auto run() -> void {
  u32 n;
  std::cin >> n;

  FixedDensePrime primes;

  while (n-- > 0) {
    u32 num;
    std::cin >> num;
    u64 τ{1LL};
    primes.forPowers(num, [&τ](int power) { τ *= power + 1; });

    std::cout << τ << "\n";
  }
}

}  // namespace _CountingDivisors

int main() {
#ifdef ANTUMBRA
  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0)
    _CountingDivisors::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
