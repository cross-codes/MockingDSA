#include <cstdint>
#include <iostream>

namespace Debug {

#ifdef CROSS

template <typename T>
concept Iterable = requires(T a) {
  { std::begin(a) } -> std::input_iterator;
  { std::end(a) } -> std::input_iterator;
} && !std::same_as<T, std::string>;

template <Iterable T>
std::ostream &operator<<(std::ostream &os, const T &container) {
  os << "{";

  bool first = true;
  for (const auto &item : container) {
    if (!first)
      os << ", ";
    os << item;
    first = false;
  }

  os << "}";
  return os;
}

void print() { std::cerr << ""; }

template <typename T, typename... Args> void print(T first, Args... args) {
  std::cerr << first << " ";
  print(args...);
  std::cerr << "\n";
}

#else

void print() {}
template <typename T, typename... Args> void print(T first, Args... args) {}

#endif
}; // namespace Debug

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  

  return 0;
}
