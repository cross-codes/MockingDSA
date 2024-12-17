package neetcode.practice.One_Dimensional_Dynamic_Programming;

import java.util.ArrayList;
import java.util.stream.IntStream;

class Solution {
  public int maximumProductInNonZeroArray(ArrayList<Integer> array) {
    int n = array.size();
    if (n == 1)
      return array.get(0);

    ArrayList<Integer> negativeIndices = new ArrayList<>();
    for (int i = 0; i < n; i++)
      if (array.get(i) < 0)
        negativeIndices.add(i);

    int[] prefix = new int[n], suffix = new int[n];
    prefix[0] = array.get(0);
    suffix[n - 1] = array.get(n - 1);
    for (int i = 1; i < n; i++)
      prefix[i] = array.get(i) * prefix[i - 1];

    for (int i = n - 2; i >= 0; i--)
      suffix[i] = array.get(i) * suffix[i + 1];

    if (negativeIndices.size() % 2 == 0)
      return array.stream().reduce(1, (a, b) -> a * b);
    else {
      ArrayList<Integer> products = new ArrayList<>();
      int lastStart = negativeIndices.get(negativeIndices.size() - 1) + 1;
      int firstEnd = negativeIndices.get(0) - 1;
      if (lastStart < n)
        products.add(suffix[lastStart]);
      if (firstEnd >= 0)
        products.add(prefix[firstEnd]);

      for (int i = 0; i < negativeIndices.size(); i++) {
        if (i % 2 == 0 && negativeIndices.get(i) + 1 < n)
          products.add(suffix[negativeIndices.get(i) + 1]);
        else if (i < negativeIndices.size() - 1 && negativeIndices.get(i + 1) - 1 >= 0)
          products.add(prefix[negativeIndices.get(i + 1) - 1]);
      }

      return products.stream().max(Integer::compareTo).orElse(0);
    }
  }

  public int maxProduct(int[] nums) {
    ArrayList<ArrayList<Integer>> potentialSubarrays = new ArrayList<>();
    ArrayList<Integer> subarray = new ArrayList<>();
    boolean containsZero = false;
    for (int i = 0; i < nums.length; i++) {
      if (nums[i] != 0)
        subarray.add(nums[i]);
      else if (!subarray.isEmpty()) {
        potentialSubarrays.add(subarray);
        subarray = new ArrayList<>();
        containsZero = true;
      }
    }
    if (!subarray.isEmpty())
      potentialSubarrays.add(subarray);

    int numberOfSubarrays = potentialSubarrays.size();
    IntStream.Builder productStream = IntStream.builder();
    for (int i = 0; i < numberOfSubarrays; i++) {
      ArrayList<Integer> array = potentialSubarrays.get(i);
      productStream.add(maximumProductInNonZeroArray(array));
    }

    int maxProduct = productStream.build().max().orElse(0);

    return maxProduct < 0 ? (containsZero ? 0 : maxProduct) : maxProduct;
  }
}