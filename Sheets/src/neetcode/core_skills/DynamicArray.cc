#include <cstddef>
#include <cstdlib>

class DynamicArray
{
private:
  int *array_;
  size_t capacity_;
  size_t back_;

  void ensure_capacity_()
  {
    if (back_ == capacity_)
    {
      capacity_ <<= 1;
      array_ =
          static_cast<int *>(std::realloc(array_, sizeof(int) * capacity_));
    }
  }

public:
  DynamicArray(int capacity) : capacity_(capacity), back_(0)
  {
    array_ = static_cast<int *>(std::malloc(sizeof(int) * capacity));
  }

  int get(int i)
  {
    return array_[i];
  }

  void set(int i, int n)
  {
    ensure_capacity_();
    array_[i] = n;
  }

  void pushback(int n)
  {
    ensure_capacity_();
    array_[back_] = n;
    back_ += 1;
  }

  int popback()
  {
    int res = array_[back_ - 1];
    back_ -= 1;
    return res;
  }

  void resize()
  {
    capacity_ <<= 1;
    array_ = static_cast<int *>(std::realloc(array_, sizeof(int) * capacity_));
  }

  int getSize()
  {
    return static_cast<int>(back_);
  }

  int getCapacity()
  {
    return static_cast<int>(capacity_);
  }
};
