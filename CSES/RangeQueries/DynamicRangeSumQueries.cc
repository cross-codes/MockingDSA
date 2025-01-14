#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

struct FenwickTree {
private:
  size_t N;
  int64_t *tree;

public:
  int64_t *array;

  FenwickTree(size_t n)
      : N(n), tree(new int64_t[n + 1]), array(new int64_t[n + 1]) {};

  void add(size_t k, int64_t x) {
    while (k <= N) {
      tree[k] += x;
      k += (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
  }

  int64_t sumq(size_t k) {
    int64_t s = 0LL;
    while (k >= 1) {
      s += tree[k];
      k -= (k == 0 ? 0 : 1 << __builtin_ctzl(k));
    }
    return s;
  }
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q;
  std::cin >> n >> q;

  FenwickTree bit = FenwickTree(n);

  for (int i = 1; i <= n; i++) {
    i64 num;
    std::cin >> num;
    bit.add(i, num);
    bit.array[i] = num;
  }

  while (q-- > 0) {
    int choice;
    std::cin >> choice;
    if (choice == 1) {
      int k;
      std::cin >> k;
      i64 u;
      std::cin >> u;
      bit.add(k, u - bit.array[k]);
      bit.array[k] = u;
    } else {
      int a, b;
      std::cin >> a >> b;
      std::cout << (bit.sumq(b) - bit.sumq(a - 1)) << "\n";
    }
  }

  return 0;
}
