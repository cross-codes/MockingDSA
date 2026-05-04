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

namespace _DownloadSpeed {

enum class EdgeType { FORWARD, BACKWARD };

class Edge {
 public:
  int from, to;
  EdgeType type;
  int64_t assigned_capacity, flow;
  std::weak_ptr<Edge> rev;

  Edge(int from, int to, int64_t capacity, EdgeType type)
      : from{from}, to{to}, type{type}, assigned_capacity{capacity}, flow{0} {}

  auto residual_capacity() -> int64_t { return assigned_capacity - flow; }
};

template <typename T>
class ResettableQueue {
 public:
  ResettableQueue(size_t n) : m_queue(n), m_head(0), m_tail(0) {}

  void reset() { m_head = m_tail = 0; }

  auto empty() -> bool { return m_head >= m_tail; }

  void push(const T& e) {
    m_queue[m_tail] = e;
    m_tail += 1;
  }

  auto front() -> T { return m_queue[m_head]; }

  void pop() { m_head += 1; }

 private:
  std::vector<T> m_queue;
  ssize_t m_head, m_tail;
};

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::shared_ptr<Edge>>> res_adj(n);
  for (int i = 0, a, b, c; i < m; i++) {
    std::cin >> a >> b >> c;
    a -= 1;
    b -= 1;

    auto fwd = std::make_shared<Edge>(a, b, c, EdgeType::FORWARD);
    auto bck = std::make_shared<Edge>(b, a, 0, EdgeType::BACKWARD);
    fwd->rev = bck;
    bck->rev = fwd;
    res_adj[a].push_back(fwd);
    res_adj[b].push_back(bck);
  }

  std::vector<std::shared_ptr<Edge>> edge_to(n);
  std::vector<int> visited(n);
  int iteration{};
  ResettableQueue<int> queue(n);

  auto bottleneck = [&]() -> int64_t {
    int64_t mn{INT64_MAX};
    for (int v = n - 1; v != 0; v = edge_to[v]->from) {
      mn = std::min(mn, edge_to[v]->residual_capacity());
    }

    return mn;
  };

  auto augment = [&]() -> void {
    int64_t b = bottleneck();
    for (int v = n - 1; v != 0; v = edge_to[v]->from) {
      auto e = edge_to[v];
      e->flow += b;
      e->rev.lock()->flow -= b;
    }
  };

  auto s_t_reachable = [&]() -> bool {
    iteration += 1;
    queue.reset();

    queue.push(0);
    visited[0] = iteration;
    while (!queue.empty()) {
      int u = queue.front();
      queue.pop();

      for (const auto& e : res_adj[u]) {
        int v = e->to;
        if (visited[v] != iteration && e->residual_capacity() > 0) {
          visited[v] = iteration;
          edge_to[v] = e;
          queue.push(v);

          if (v == n - 1) {
            return true;
          }
        }
      }
    }

    return false;
  };

  while (s_t_reachable()) {
    augment();
  }

  int64_t max_flow{};
  for (auto e : res_adj[0]) {
    if (e->type == EdgeType::FORWARD) {
      max_flow += e->flow;
    }
  }

  std::cout << max_flow << "\n";
}

}  // namespace _DownloadSpeed

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
    _DownloadSpeed::run();

  std::cout.flush();

  return 0;
}
