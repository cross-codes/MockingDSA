import java.util.Arrays;

class Solution {
  public int minimumCost(int[] cost) {
    Arrays.sort(cost);
    int tot = 0, i = cost.length - 1;
    for (; i >= 1; i -= 3) {
      tot += cost[i] + cost[i - 1];
    }

    if (i == 0)
      tot += cost[0];

    return tot;
  }
}
