#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

#pragma float_control(precise, off)

using namespace std;
using namespace __gnu_pbds;

typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

class HasherFunctor {
private:
  static uint64_t random_address() {
    char *p = new char;
    delete p;
    return uint64_t(p);
  }

  static uint32_t hash_32(uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static uint64_t splitmix_64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> uint64_t operator()(T x) const {
    static const uint64_t FIXED_RANDOM =
        splitmix_64(chrono::steady_clock::now().time_since_epoch().count() *
                    (random_address() | 1));
    return sizeof(x) <= 4 ? hash_32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix_64(x ^ FIXED_RANDOM);
  }
};

i32 main(i32 argc, char **argv) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  gp_hash_table<i32, i32, ::HasherFunctor> int_to_frequency_1{};
  gp_hash_table<i32, i32, ::HasherFunctor> int_to_frequency_2{};

  i32 x, y;
  while (cin >> x >> y) {
    int_to_frequency_1[x] += 1;
    int_to_frequency_2[y] += 1;
  }

  i64 similarity_score = 0;
  for (const pair<const i32, i32> &entry : int_to_frequency_1) {
    int number = entry.first, occurences_in_first = entry.second;
    int occurences_in_second = int_to_frequency_2[number];
    similarity_score += (number * occurences_in_second) * occurences_in_first;
  }

  cout << similarity_score << "\n";
  return 0;
}