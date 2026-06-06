import java.util.Arrays;

class Solution {
  public boolean asteroidsDestroyed(long mass, int[] asteroids) {
    Arrays.sort(asteroids);

    boolean ok = true;
    for (int e : asteroids) {
      ok &= (mass >= e);
      mass += e;
    }

    return ok;
  }
}
