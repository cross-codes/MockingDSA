package neetcode.practice.Sliding_Window;

class Solution {
  public int maxProfit(int[] prices) {
    int bestProfit = 0, currentProfit = 0, currentBought = prices[0];
    for (int index = 0; index < prices.length; index++) {
      int currentSellingPrice = prices[index];
      if (currentSellingPrice < currentBought)
        currentBought = currentSellingPrice;
      else {
        currentProfit = currentSellingPrice - currentBought;
        bestProfit = Math.max(bestProfit, currentProfit);
      }
    }

    return bestProfit;
  }
}