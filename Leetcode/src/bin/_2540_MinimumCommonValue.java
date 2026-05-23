class Solution {
  public int getCommon(int[] nums1, int[] nums2) {
    int n = nums1.length, m = nums2.length, i = 0, j = 0;
    while (i < n) {
      while (j < m && nums2[j] < nums1[i])
        j++;

      if (j >= m)
        break;

      if (nums1[i] == nums2[j])
        return nums1[i];

      i += 1;
    }

    return -1;
  }
}
