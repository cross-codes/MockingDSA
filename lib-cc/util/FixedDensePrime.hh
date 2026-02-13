#include <array>
#include <bitset>
#include <functional>
#include <memory>
#include <vector>

template <size_t N>
class FixedDensePrime {
 public:
  std::vector<int> primes_;

  explicit FixedDensePrime() : m_minima{}, m_powers{} {
    for (int i = 2; i < (N + 1) >> 1; i++) {
      int minimum, power;
      if (m_minima[i] == 0) {
        minimum = i;
        power   = 1;
        m_parity.set(i, true);
        m_square_free.set(i, true);
        primes_.push_back(i);
      } else {
        minimum = m_minima[i];
        power   = m_powers[i];
      }

      for (int e : primes_) {
        int index{e * i};
        if (index < N) {
          m_minima[index] = e;
          m_parity.set(index, !m_parity[i]);
          if (e == minimum) {
            m_powers[index] = power + 1;
            break;
          } else {
            m_powers[index] = 1;
            m_square_free.set(index, m_square_free[i]);
          }
        } else
          break;
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2) {
      if (m_minima[i] == 0) {
        m_parity.set(i, true);
        m_square_free.set(i, true);
      }
    }
  }

  auto is_square_free(int n) -> bool { return m_square_free[n]; }
  auto get_parity(int n) -> bool { return m_parity[n]; }

  auto totient(int n) -> int {
    int result{1};
    while (m_minima[n] != 0) {
      int factor{1};
      for (int i = 1; i < m_powers[n]; i++)
        factor *= m_minima[n];
      result *= factor * (m_minima[n] - 1);
      n /= factor * m_minima[n];
    }

    if (n != 1)
      result *= n - 1;

    return result;
  }

  void for_prime_factors(int n, std::function<void(const int&)> consume) {
    while (m_minima[n] != 0) {
      consume(m_minima[n]);
      int factor{1};
      for (int i = 0; i < m_powers[n]; i++)
        factor *= m_minima[n];
      n /= factor;
    }

    if (n != 1)
      consume(n);
  }

  void for_powers(int n, std::function<void(const int&)> consume) {
    while (m_minima[n] != 0) {
      consume(m_powers[n]);
      int factor{1};
      for (int i = 0; i < m_powers[n]; i++)
        factor *= m_minima[n];
      n /= factor;
    }

    if (n != 1)
      consume(1);
  }

  void for_prime_factors_and_powers(
      int n,
      std::function<void(const int&, const int&)> biConsume) {
    while (m_minima[n] != 0) {
      biConsume(m_minima[n], m_powers[n]);
      int factor{1};
      for (int i = 0; i < m_powers[n]; i++)
        factor *= m_minima[n];
      n /= factor;
    }

    if (n != 1)
      biConsume(n, 1);
  }

  void for_factors(int n,
                   bool include1,
                   bool includeN,
                   std::function<void(const int64_t&)> consume) {
    if (n == 1) {
      if (include1 && includeN)
        consume(1);
    } else {
      if (include1)
        consume(1);

      std::vector<int64_t> prime_factors{}, powers{};

      for_prime_factors_and_powers(n, [&prime_factors, &powers](int a, int b) {
        prime_factors.push_back(a), powers.push_back(b);
      });

      std::vector<int64_t> factors = prime_factors;
      std::unique_ptr<int[]> current_powers(new int[factors.size()]);
      std::ranges::fill(current_powers.get(),
                        current_powers.get() + factors.size(), 1);

      int index{};
      while (true) {
        if (current_powers[index] > powers[index])
          index++;
        else if (factors[index] == n) {
          if (includeN)
            consume(n);
          break;
        } else {
          consume(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * prime_factors[i];

          std::ranges::fill(current_powers.get(), current_powers.get() + index,
                            1);

          current_powers[index]++;
          index = 0;
        }
      }
    }
  }

 private:
  std::array<int, N> m_minima, m_powers;
  std::bitset<N> m_parity, m_square_free;
};
