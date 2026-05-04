namespace _1848;

public class Solution {
    public int GetMinDistance(int[] nums, int target, int start) {
        int l = start, r = start;
        while (l >= 0 || r < nums.Length) {
            if (l >= 0 && nums[l] == target) {
                return start - l;
            }

            if (r < nums.Length && nums[r] == target) {
                return r - start;
            }

            r += 1;
            l -= 1;
        }

        return -1;
    }
}
