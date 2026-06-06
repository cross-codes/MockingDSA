import java.util.function.LongToIntFunction;

class Solution {
  public int minElement(int[] nums) {
    LongToIntFunction numDigits = (n) -> {
      int s = 0;
      while (n != 0) {
        s += n % 10;
        n /= 10;
      }

      return s;
    };

    int mn = Integer.MAX_VALUE;
    for (int e : nums) {
      mn = Math.min(mn, numDigits.applyAsInt(e));
    }

    return mn;
  }
}
