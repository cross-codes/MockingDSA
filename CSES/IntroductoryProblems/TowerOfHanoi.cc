#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

void move(std::size_t, u32, u32, u32);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;
  std::cout << (1 << n) - 1 << "\n";

  ::move(n, 1, 2, 3);

  return 0;
}

void move(std::size_t numberOfDisks, u32 source, u32 intermediate, u32 destination) {
  if (numberOfDisks == 1)
    std::cout << source << " " << destination << "\n";
  else {
    ::move(numberOfDisks - 1, source, destination, intermediate);
    std::cout << source << " " << destination << "\n";
    ::move(numberOfDisks - 1, intermediate, source, destination);
  }
}
