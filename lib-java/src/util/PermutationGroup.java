package util;

import java.util.Arrays;
import java.util.Comparator;

class PermutationGroup {
  private static <T> ReverseIterator<T> isSortedUntil(ReverseIterator<T> first, ReverseIterator<T> last,
      Comparator<? super T> comp) {
    if (first.equals(last))
      return last;
    ReverseIterator<T> prev = first;
    ReverseIterator<T> it = new ReverseIterator<>(first.array, first.index - 1);
    while (!it.equals(last)) {
      if (comp.compare(it.get(), prev.get()) < 0) {
        return it;
      }
      prev = it;
      it = new ReverseIterator<>(it.array, it.index - 1);
    }
    return last;
  }

  private static <T> void reverse(T[] array, int fromIndex, int toIndex) {
    for (int i = fromIndex, j = toIndex - 1; i < j; i++, j--) {
      T temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }

  private static <T> ReverseIterator<T> upperBound(ReverseIterator<T> first, ReverseIterator<T> last, T value,
      Comparator<? super T> comp) {
    int low = last.base();
    int high = first.base() - 1;
    int ans = last.base() - 1;

    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (comp.compare(first.array[mid], value) > 0) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    return new ReverseIterator<>(first.array, ans + 1);
  }

  public static boolean nextPermutation(byte[] input) {
    Byte[] s = new Byte[input.length];
    Arrays.setAll(s, i -> input[i]);

    ReverseIterator<Byte> rFirst = new ReverseIterator<>(s, s.length);
    ReverseIterator<Byte> rLast = new ReverseIterator<>(s, 0);

    ReverseIterator<Byte> left = isSortedUntil(rFirst, rLast, Byte::compareTo);

    if (left.equals(rLast)) {
      reverse(s, 0, s.length);

      for (int i = 0; i < input.length; i++) {
        input[i] = s[i].byteValue();
      }

      return false;
    }

    ReverseIterator<Byte> right = upperBound(rFirst, left, left.get(), Byte::compareTo);
    left.iterSwap(right);

    reverse(s, left.base(), s.length);
    for (int i = 0; i < input.length; i++) {
      input[i] = s[i].byteValue();
    }
    return true;
  }
}
