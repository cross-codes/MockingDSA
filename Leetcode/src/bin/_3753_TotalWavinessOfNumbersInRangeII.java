import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.function.LongFunction;

class Solution {
  public long totalWaviness(long num1, long num2) {
    Map<ParametersT, LongOrderedPair> lookup = new HashMap<>();
    String[] s = new String[1];

    DFS call = (instance, i, prev, prev2, equal, empty) -> {
      if (i == s[0].length()) {
        return new LongOrderedPair(1, 0);
      }

      ParametersT parameters = new ParametersT(i, prev, prev2, empty);
      if (!equal && lookup.containsKey(parameters)) {
        return lookup.get(parameters);
      }

      LongOrderedPair res = new LongOrderedPair(0, 0);
      int limit = equal ? s[0].charAt(i) - '0' : 9;

      for (int d = 0; d <= limit; d++) {
        boolean nextEmpty = empty && (d == 0);
        boolean nextEqual = equal && (d == limit);

        int nextPrev2, nextPrev;
        int waveIncrement = 0;

        if (empty) {
          if (d == 0) {
            nextPrev2 = -1;
            nextPrev = -1;
          } else {
            nextPrev2 = -1;
            nextPrev = d;
          }
        } else {
          if (prev2 != -1) {
            if ((prev > prev2 && prev > d) || (prev < prev2 && prev < d)) {
              waveIncrement = 1;
            }
          }
          nextPrev2 = prev;
          nextPrev = d;
        }

        var nextRes = instance.run(instance, i + 1, nextPrev, nextPrev2, nextEqual, nextEmpty);

        res.first += nextRes.first;
        res.second += nextRes.second + (waveIncrement * nextRes.first);
      }

      if (!equal) {
        lookup.put(parameters, res);
      }
      return res;
    };

    LongFunction<Long> digitSum = (long x) -> {
      if (x < 0)
        return 0L;
      s[0] = Long.toString(x);
      lookup.clear();
      return call.run(call, 0, -1, -1, true, true).second;
    };

    return digitSum.apply(num2) - digitSum.apply(num1 - 1);
  }

  @FunctionalInterface
  private interface DFS {
    LongOrderedPair run(DFS instance, int i, int prev, int prev2, boolean equal, boolean empty);
  }

  private record ParametersT(int i, int prev, int prev2, boolean empty) {
  }
}

class LongOrderedPair {
  public long first;
  public long second;

  public LongOrderedPair(long first, long second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof LongOrderedPair))
      return false;
    LongOrderedPair pair = (LongOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
