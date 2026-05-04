#include <vector>

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
