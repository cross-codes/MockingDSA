#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _JosephusProblemII {

template <std::integral T>
class BinarySearchTree {
 private:
  struct Node {
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left, right;
    T value;

    Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right, T value)
        : left(left), right(right), value(value) {};
  };

  std::shared_ptr<Node> root;
  std::vector<std::shared_ptr<Node>> leaves;

 public:
  BinarySearchTree(size_t n) {
    if (n < 1) {
      n = 1;
    }

    leaves.resize(std::bit_floor(n) << 1);
    for (size_t i = 0; i < leaves.size(); i++) {
      leaves[i] = std::make_shared<Node>(nullptr, nullptr, T{});
    }
  }

  void set(int element) { leaves[element]->value = 1; }

  void build() {
    std::vector<std::shared_ptr<Node>> nodes = leaves;

    while (nodes.size() != 1) {
      std::vector<std::shared_ptr<Node>> new_nodes{};
      new_nodes.resize(nodes.size() >> 1);

      for (size_t i = 0; i < new_nodes.size(); i++) {
        auto left  = nodes[i * 2];
        auto right = nodes[i * 2 + 1];
        new_nodes[i] =
            std::make_shared<Node>(left, right, left->value + right->value);

        left->parent = right->parent = new_nodes[i];
      }

      nodes = new_nodes;
    }
    root = nodes[0];
  }

  auto size() const -> T { return root->value; }

  auto contains(int element) const -> bool {
    return leaves[element]->value != 0;
  }

  auto order_of_key(T x) const -> int {
    int index{};
    for (auto node = leaves[x]; node != root;) {
      auto p = node->parent.lock();
      if (!p) {
        break;
      }

      if (p->right == node) {
        index += p->left->value;
      }
      node = p;
    }

    return leaves[x]->value == 0 ? -index - 1 : index;
  }

  void add(int element) {
    for (auto node = leaves[element]; node != nullptr;) {
      node->value += 1;
      node = node->parent.lock();
    }
  }

  void remove_one(int element) {
    for (auto node = leaves[element]; node != nullptr;) {
      node->value -= 1;
      node = node->parent.lock();
    }
  }

  auto find_by_order(int k) const -> T {
    if (!root) {
      return 0;
    }

    T element{};
    size_t step = leaves.size() >> 1;

    for (auto node = root; node->left != nullptr; step >>= 1) {
      if (k < node->left->value) {
        node = node->left;
      } else {
        k -= node->left->value;
        element += step;
        node = node->right;
      }
    }

    return element;
  }
};

auto run() -> void {
  int n, k;
  std::cin >> n >> k;

  BinarySearchTree<int> bst(n + 1);
  for (int i = 1; i <= n; i++) {
    bst.set(i);
  }

  bst.build();

  int cur_pos{};
  while ((n = bst.size()) != 0) {
    int nxt_pos = (cur_pos + k) % n;
    int val     = bst.find_by_order(nxt_pos);
    std::cout << val << " ";

    bst.remove_one(val);
    cur_pos = nxt_pos;
  }

  std::cout << "\n";
}

}  // namespace _JosephusProblemII

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
    _JosephusProblemII::run();

  std::cout.flush();

  return 0;
}
