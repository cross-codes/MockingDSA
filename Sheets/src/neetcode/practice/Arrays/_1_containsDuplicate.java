package neetcode.practice.Arrays;

import java.util.HashSet;

class Solution {
  public boolean hasDuplicate(int[] nums) {
    HashSet<Integer> set = new HashSet<>();
    for (int i : nums) {
      if (set.contains(i))
        return true;
      else
        set.add(i);
    }
    return false;
  } 
}