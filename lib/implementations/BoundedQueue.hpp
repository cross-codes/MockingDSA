#include <cstddef>
#include <cstdint>
#include <memory>

template <typename E> struct BoundedQueue {
private:
  int64_t QUEUE_SIZE_;
  int64_t head_, tail_;
  std::unique_ptr<E[]> queue_;

public:
  BoundedQueue(size_t initialSize)
      : QUEUE_SIZE_(initialSize + 1), head_(0), tail_(0),
        queue_(std::make_unique<E[]>(QUEUE_SIZE_)) {}

  void enqueue(E element) {
    if (tail_ + 1 == head_ || ((tail_ == QUEUE_SIZE_ - 1) && head_ == 0))
      throw head_;

    queue_[tail_] = element;
    if (tail_ == QUEUE_SIZE_ - 1)
      tail_ = 0;
    else
      tail_++;
  }

  E dequeue() {
    if (head_ == tail_)
      throw head_;

    E value = queue_[head_];
    if (head_ == QUEUE_SIZE_ - 1)
      head_ = 1;
    else
      head_++;

    return value;
  }
};
