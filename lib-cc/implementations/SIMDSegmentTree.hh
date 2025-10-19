#include <cmath>
#include <utility>

template <class T, int N, class F> struct SIMDSegTree
{
  static constexpr int cache_size     = 64;
  static constexpr int reg_size       = 32;
  static constexpr int reg_count      = cache_size / reg_size;
  static constexpr int branching      = cache_size / sizeof(T);
  static constexpr int branching_bits = std::__lg(branching);
  typedef T __attribute__((vector_size(reg_size))) vec;

  struct Precalc
  {
    alignas(cache_size) T mask[branching][branching];
    constexpr Precalc() : mask{}
    {
      for (int i = 0; i < branching; ++i)
        for (int j = 0; j < branching; ++j)
          mask[i][j] = (i < j ? -1 : 0);
    }
  };

  static constexpr Precalc precalc{};

  static constexpr int height(int n)
  {
    return (n <= branching ? 1 : height(n / branching) + 1);
  }

  static constexpr int calc_offset(int h)
  {
    int s = 0, n = N;
    while (h--)
    {
      s += (n + branching - 1) / branching * branching;
      n /= branching;
    }
    return s;
  }

  static constexpr int round(int k)
  {
    return k & ~(branching - 1);
  }

  static constexpr int H = height(N);

  template <std::size_t... indices>
  static constexpr std::array<int, H + 1> calc_offsets(
      std::index_sequence<indices...>)
  {
    return {calc_offset(indices)...};
  }

  static constexpr auto offset =
      calc_offsets(std::make_index_sequence<H + 1>());
  alignas(cache_size) T values[offset[H]]{};
  F &f_;

  SIMDSegTree(F &f) : f_(f)
  {
  }

  void prefetch(int h, int i)
  {
    __builtin_prefetch(values + offset[h] + round(i));
  }

  void add(int k, T x)
  {
    vec v = x + vec{};
    for (int h = 0; h != H; ++h)
    {
      if (h + 1 != H)
        prefetch(h + 1, k >> branching_bits);
      auto a       = (vec *)&values[offset[h] + round(k)];
      const auto m = (const vec *)&precalc.mask[k % branching];
      for (int i = 0; i != reg_count; ++i)
        a[i] = f_(a[i], v & m[i]);
      k >>= branching_bits;
    }
  }

  T sum(int i)
  {
    T s = 0;
    for (int h = 0; h != H; ++h)
    {
      if (h + 1 != H)
        prefetch(h + 1, i >> branching_bits);
      s = f_(s, values[offset[h] + i]);
      i >>= branching_bits;
    }
    return s;
  }

  T sum(int i, int j)
  {
    T s = 0;
    for (int h = 0; h != H; ++h)
    {
      if (h + 1 != H)
      {
        prefetch(h + 1, i >> branching_bits);
        if (i >> branching_bits != j >> branching_bits)
          prefetch(h + 1, j >> branching_bits);
      }
      s = f_(s, -values[offset[h] + i]);
      s = f_(s, +values[offset[h] + j]);
      i >>= branching_bits;
      j >>= branching_bits;
    }
    return s;
  }
};
