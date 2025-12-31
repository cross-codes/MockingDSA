#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <deque>
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <utility>   // IWYU pragma: keep
#include <vector>    // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _RoomAllocation {

enum TimeType { INCOMING, OUTGOING };

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<std::tuple<int, TimeType, int>> intervals{};
  for (int i = 0, a, b; i < n; i++) {
    std::cin >> a >> b;
    intervals.push_back({a, TimeType::INCOMING, i});
    intervals.push_back({b, TimeType::OUTGOING, i});
  }

  std::sort(intervals.begin(), intervals.end());

  std::deque<int> free_rooms{};
  std::vector<int> allotment_history(n);
  int cur{}, mx{}, nxt_room{1};
  for (const auto& [e, t, i] : intervals) {
    if (t == TimeType::INCOMING) {
      cur += 1;
      int room{-1};
      if (free_rooms.empty()) {
        room = nxt_room;
        nxt_room += 1;
      } else {
        room = free_rooms.back();
        free_rooms.pop_back();
      }
      allotment_history[i] = room;
    } else {
      cur -= 1;
      int room = allotment_history[i];
      free_rooms.push_back(room);
    }

    mx = std::max(mx, cur);
  }

  std::cout << mx << "\n";

  for (int e : allotment_history) {
    std::cout << e << " ";
  }

  std::cout << "\n";
}

}  // namespace _RoomAllocation

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _RoomAllocation::run();

  std::cout.flush();

  return 0;
}
