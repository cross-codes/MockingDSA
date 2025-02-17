#include <cstdint>
#include <iostream>
#include <stack>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;
  std::stack<std::pair<int, int>> stack{};

  for (std::size_t i = 0; i < n; i++) {
    int num;
    std::cin >> num;

    if (stack.empty())
      std::cout << "0 ";
    else if (num > stack.top().first)
      std::cout << stack.top().second << " ";
    else {
      while (!stack.empty() && stack.top().first >= num)
        stack.pop();

      if (stack.empty())
        std::cout << "0 ";
      else
        std::cout << stack.top().second << " ";
    }

    stack.push({num, i + 1});
  }

  std::cout << "\n";

  return 0;
}
