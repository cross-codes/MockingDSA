#include <stack>

template <typename F, typename T>
  requires std::invocable<F, T, T>
class AggregateQueue {
 private:
  class AggregateStack {
   public:
    std::stack<std::pair<T, T>> stack;

    AggregateStack() {}

    void push(T x) {
      T curr_agg = stack.empty() ? x : F()(stack.top().second, x);
      stack.push(std::make_pair(x, curr_agg));
    }

    void pop() { stack.pop(); }

    auto aggregate() -> T { return stack.top().second; }
  };

  AggregateStack in, out;

 public:
  AggregateQueue() {}

  void push_back(T x) { in.push(x); }

  void pop_front() {
    if (out.stack.empty()) {
      while (!in.stack.empty()) {
        T val = in.stack.top().first;
        in.pop();
        out.push(val);
      }
    }
    out.pop();
  }

  auto query() -> T {
    if (in.stack.empty())
      return out.aggregate();

    if (out.stack.empty())
      return in.aggregate();

    return F()(in.aggregate(), out.aggregate());
  }
};
