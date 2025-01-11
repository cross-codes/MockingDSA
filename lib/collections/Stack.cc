#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

template <typename E> class Stack {
private:
  int STACK_SIZE_;
  int pos_ = -1;

public:
  bool isUnbound;

private:
  E *stack_;

public:
  Stack(int initialSize, bool isUnbound)
      : STACK_SIZE_(initialSize), isUnbound(isUnbound) {
    stack_ = new E[STACK_SIZE_];
    std::memset(stack_, 0, sizeof(E) * STACK_SIZE_);
  };

  ~Stack() { delete[] stack_; }

  void ensureCapacity() {
    if (isUnbound) {
      if (pos_ == STACK_SIZE_ - 1) {
        E *newStack = new E[STACK_SIZE_ << 1];
        std::memcpy(newStack, stack_, STACK_SIZE_ * sizeof(E));
        delete[] stack_;

        stack_ = newStack;
        STACK_SIZE_ <<= 1;
      }
    }
  }

  E pop() {
    if (pos_ == -1)
      throw pos_;
    return stack_[pos_--];
  }

  void push(E element) {
    if (!isUnbound && pos_ >= STACK_SIZE_ - 1)
      throw STACK_SIZE_;
    ensureCapacity();
    stack_[++pos_] = element;
  }

  bool isEmpty() { return pos_ == -1; }
  size_t size() { return pos_ + 1; }
  void clear() {
    std::memset(stack_, 0, sizeof(E) * STACK_SIZE_);
    pos_ = -1;
  }

  E peek() {
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
