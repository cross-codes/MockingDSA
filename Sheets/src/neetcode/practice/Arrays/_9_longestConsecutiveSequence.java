package neetcode.practice.Arrays;

import java.util.HashSet;

class Solution {
  public int longestConsecutive(int[] nums) {
    HashSet<Integer> uniqueElements = new HashSet<>() {
      {
        for (int i : nums)
          this.add(i);
      }
    };

    int longestLength = 0, currentLength = 1;
    for (int i = 0; i < nums.length; i++) {
      int num = nums[i];
      if (!uniqueElements.contains(num - 1)) {
        while (true) {
          if (uniqueElements.contains(++num))
            currentLength++;
          else
            break;
        }
      }
      longestLength = Math.max(currentLength, longestLength);
      currentLength = 1;
    }

    return longestLength;
  }
}