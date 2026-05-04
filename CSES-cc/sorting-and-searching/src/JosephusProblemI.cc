#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <cmath>      // IWYU pragma: keep
#include <cstdint>    // IWYU pragma: keep
#include <cstring>    // IWYU pragma: keep
#include <iostream>   // IWYU pragma: keep
#include <memory>
#include <string>   // IWYU pragma: keep
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _JosephusProblemI {

class DoublyLinkedNode {
 public:
  int value;
  std::shared_ptr<DoublyLinkedNode> prev{nullptr}, next{nullptr};

  DoublyLinkedNode(int value) : value{value} {};
};

auto run() -> void {
  int n;
  std::cin >> n;

  std::shared_ptr<DoublyLinkedNode> head =
                                        std::make_shared<DoublyLinkedNode>(1),
                                    curr = head;

  for (int i = 2; i <= n; i++) {
    std::shared_ptr<DoublyLinkedNode> next_node =
        std::make_shared<DoublyLinkedNode>(i);
    curr->next      = next_node;
    next_node->prev = curr;
    curr            = next_node;
  }

  curr->next = head;
  head->prev = curr;

  curr       = head;
  while (curr->next != curr || curr->prev != curr) {
    auto rep = curr->next;
    std::cout << rep->value << " ";
    curr->next      = rep->next;
    rep->next->prev = curr;
    curr            = curr->next;
  }

  std::cout << curr->value << "\n";
}

}  // namespace _JosephusProblemI

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
    _JosephusProblemI::run();

  std::cout.flush();

  return 0;
}
