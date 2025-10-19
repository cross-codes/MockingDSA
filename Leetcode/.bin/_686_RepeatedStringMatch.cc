#include <random>
#include <string>

class Solution
{
private:
  struct StringHash
  {
  private:
    int n;

  public:
    std::vector<int> powers{}, prefix_hashes{};
    int64_t A;
    int B;

    StringHash(const std::string &s, int64_t _A, int _B)
        : n(static_cast<int>(s.length())), powers(n + 1, 1),
          prefix_hashes(n + 1, 0), A{_A}, B{_B}
    {
      for (int i = 1; i <= n; i++)
      {
        powers[i] = powers[i - 1] * A % B;
        prefix_hashes[i] =
            (prefix_hashes[i - 1] * A + static_cast<int64_t>(s[i - 1])) % B;
      }
    }

    int get_hash(int l, int r)
    {
      int64_t h = static_cast<int64_t>(prefix_hashes[r]) -
                  static_cast<int64_t>(prefix_hashes[l]) * powers[r - l];
      return (h % B + B) % B;
    }
  };

public:
  int repeatedStringMatch(std::string a, std::string b)
  {
    auto a_cpy = a;
    std::mt19937_64 rng;
    std::random_device rd;
    rng.seed(rd());

    int B     = static_cast<int>(1e9 - 7);
    int64_t A = std::uniform_int_distribution<int64_t>(
        B / 10, 9 * static_cast<int64_t>(B) / 10)(rng);

    int k = static_cast<int>(b.size());
    StringHash ht(b, A, B);
    int target = ht.get_hash(0, k);

    auto test  = [&a, &target, &k, &A, &B]() -> bool {
      StringHash ho(a, A, B);
      int n = static_cast<int>(a.size());

      for (int i = 0; i < n - k + 1; i++)
      {
        int hash_a = ho.get_hash(i, i + k);
        if (hash_a == target)
          return true;
      }

      return false;
    };

    int cnt{1};
    while (a.size() < b.size())
    {
      a += a_cpy;
      cnt += 1;
    }

    if (test())
      return cnt;

    a += a_cpy;
    if (test())
      return cnt + 1;
    else
      return -1;
  }
};
