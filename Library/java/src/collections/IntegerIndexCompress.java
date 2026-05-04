package collections;

import java.util.Arrays;

public class IntegerIndexCompress {
  private final int[] arr;
  private final int size;

  public IntegerIndexCompress(int[] vec) {
    this.arr = vec;
    Arrays.sort(this.arr);

    int unique = 0;
    if (this.arr.length > 0) {
      unique = 1;
      for (int i = 1; i < this.arr.length; i++) {
        if (this.arr[i] != this.arr[i - 1]) {
          this.arr[unique++] = this.arr[i];
        }
      }
    }

    this.size = unique;
  }

  public int getCompressedIndex(int value) {
    int index = Arrays.binarySearch(this.arr, 0, this.size, value);
    return index >= 0 ? index : ~index;
  }

  public int getMaxRange() {
    return this.size - 1;
  }
}
