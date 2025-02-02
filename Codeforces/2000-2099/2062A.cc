#include <cstdint>
#include <cstdio>
#include <sys/types.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {

  int t;
  std::scanf("%d", &t);

  dbg(t);

  while (t-- > 0) {
    char string[51];
    std::scanf("%s", string);

    int cnt = 0;
    for (char c : string) {
      if (c == '1')
        cnt++;
    }

    std::printf("%d\n", cnt);
  }

  return 0;
}
