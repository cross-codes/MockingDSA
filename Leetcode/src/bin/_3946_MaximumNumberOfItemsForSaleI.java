class Solution {
  public int maximumSaleItems(int[][] items, int budget) {
    int n = items.length, mnc = Integer.MAX_VALUE;
    int[] nfcs = new int[n];
    for (int i = 0; i < n; i++) {
      int nfc = 0;
      for (int j = 0; j < n; j++) {
        if (i == j)
          continue;
        if (items[j][0] % items[i][0] == 0)
          nfc += 1;
      }

      nfcs[i] = 1 + nfc;
      mnc = Math.min(mnc, items[i][1]);
    }

    int[][] mxv = new int[n][1 + budget];
    for (int i = 0; i < n; i++) {
      for (int w = 0; w <= budget; w++) {
        if (i == 0) {
          mxv[i][w] = (w >= items[i][1]) ? nfcs[i] : 0;
        } else {
          mxv[i][w] = mxv[i - 1][w];
          if (w >= items[i][1]) {
            mxv[i][w] = Math.max(mxv[i][w], mxv[i - 1][w - items[i][1]] + nfcs[i]);
          }
        }
      }
    }

    int mxvv = 0;
    for (int w = 0; w <= budget; w++) {
      mxvv = Math.max(mxvv, mxv[n - 1][w] + (budget - w) / mnc);
    }

    return mxvv;
  }
}
