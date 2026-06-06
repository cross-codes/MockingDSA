import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
  public int[] limitOccurrences(int[] nums, int k) {
    int n = nums.length;
    int e = nums[0], cnt = 1;
    List<Integer> res = new ArrayList<>(Arrays.asList(e));
    for (int i = 1; i < n; i++) {
      if (nums[i] == e) {
        cnt += 1;
        if (cnt <= k) {
          res.add(e);
        }
      } else {
        cnt = 1;
        e = nums[i];
        res.add(e);
      }
    }

    return res.stream().mapToInt(Integer::intValue).toArray();
  }
}
