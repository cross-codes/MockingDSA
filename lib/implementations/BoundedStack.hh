#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

template <typename E> class BoundedStack {

  /*
   * Author: github.com/cross-codes
   */

private:
  int64_t STACK_SIZE_;
  int64_t pos_ = -1;
  std::unique_ptr<E[]> stack_;

public:
  BoundedStack(size_t initialSize)
      : STACK_SIZE_(initialSize), stack_(std::make_unique<E[]>(STACK_SIZE_)) {};

  void pop() {
    if (pos_ == -1)
      throw pos_;
    pos_--;
  }

  void push(E element) {
    if (pos_ >= STACK_SIZE_ - 1)
      throw STACK_SIZE_;
    stack_[++pos_] = element;
  }

  bool empty() { return pos_ == -1; }

  size_t size() { return static_cast<size_t>(pos_ + 1); }

  void clear() { pos_ = -1; }

  E top() {
    if (pos_ == -1)
      throw pos_;
    return stack_[pos_];
  }

  std::string to_string() {
    std::string res = "[";
    for (int i = 0; i <= pos_; i++)
      res += std::to_string(stack_[i]) + (i == pos_ ? "" : ", ");
    return res + "]";
  }
};
