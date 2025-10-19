import java.util.HashMap;

class Solution {
  public int[] twoSum(int[] nums, int target) {
    int n = nums.length;

    HashMap<Integer, Integer> map = new HashMap<>();
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      if (map.containsKey(target - x)) {
        return new int[] { map.get(target - x), i };
      }
      map.put(x, i);
    }

    return new int[] {};
  }
}
