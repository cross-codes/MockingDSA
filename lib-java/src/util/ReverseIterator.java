package util;

class ReverseIterator<T> {
  final T[] array;
  final int index;

  public ReverseIterator(T[] array, int index) {
    this.array = array;
    this.index = index;
  }

  public T get() {
    return array[index - 1];
  }

  public int base() {
    return index;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null || getClass() != obj.getClass())
      return false;

    ReverseIterator<?> that = (ReverseIterator<?>) obj;
    return index == that.index;
  }

  public void iterSwap(ReverseIterator<T> b) {
    T temp = this.get();
    this.array[this.index - 1] = b.get();
    b.array[b.index - 1] = temp;
  }
}
