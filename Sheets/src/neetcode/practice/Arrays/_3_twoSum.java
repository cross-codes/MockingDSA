package neetcode.practice.Arrays;

import java.util.HashMap;

class Solution {
  public int[] twoSum(int[] nums, int target) {
    HashMap<Integer, Integer> map = new HashMap<>();
    int n = nums.length;
    for (int i = 0; i < n; i++)
      map.put(nums[i], i);

    for (int i = 0; i < n; i++) {
      int num = nums[i];
      if (map.containsKey(target - num)) {
        int index = map.get(target - num);
        if (index != i)
          return new int[] { Math.min(i, index), Math.max(i, index) };
      }
    }
    return null;
  }
}