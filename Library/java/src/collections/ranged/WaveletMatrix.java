package collections.ranged;

public class WaveletMatrix {
  private final int levels;
  private final int[][] pref;
  private final int[] zeroBoundary;

  public WaveletMatrix(int[] arr, int maxVal) {
    int n = arr.length;
    this.levels = 32 - Integer.numberOfLeadingZeros(Math.max(1, maxVal));

    this.pref = new int[levels][n + 1];
    this.zeroBoundary = new int[levels];

    int[] temp = new int[n];

    for (int l = levels - 1; l >= 0; l--) {
      int bit = 1 << l;
      int zeros = 0;

      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          zeros++;
        }
        pref[l][i + 1] = zeros;
      }

      zeroBoundary[l] = zeros;

      int leftIdx = 0;
      int rightIdx = zeros;
      for (int i = 0; i < n; i++) {
        if ((arr[i] & bit) == 0) {
          temp[leftIdx++] = arr[i];
        } else {
          temp[rightIdx++] = arr[i];
        }
      }

      System.arraycopy(temp, 0, arr, 0, n);
    }
  }

  public int kthSmallestOneIndexed(int from, int exclTo, int k) {
    int ans = 0;
    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];
      int zerosInInterval = zerosInRight - zerosInLeft;

      if (k <= zerosInInterval) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
        k -= zerosInInterval;
        ans |= (1 << l);
      }
    }

    return ans;
  }

  public int numEq(int from, int exclTo, int target) {
    if (target < 0 || target >= (1 << levels)) {
      return 0;
    }

    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];

      if ((target & (1 << l)) == 0) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
      }

      if (from == exclTo) {
        return 0;
      }
    }

    return exclTo - from;
  }

  public int numLeq(int from, int exclTo, int target) {
    if (target < 0) {
      return 0;
    }
    if (target >= (1 << levels)) {
      return exclTo - from;
    }

    int count = 0;

    for (int l = levels - 1; l >= 0; l--) {
      int zerosInLeft = pref[l][from];
      int zerosInRight = pref[l][exclTo];
      int zerosInInterval = zerosInRight - zerosInLeft;

      if ((target & (1 << l)) == 0) {
        from = zerosInLeft;
        exclTo = zerosInRight;
      } else {
        count += zerosInInterval;
        from = zeroBoundary[l] + (from - zerosInLeft);
        exclTo = zeroBoundary[l] + (exclTo - zerosInRight);
      }

      if (from == exclTo) {
        return count;
      }
    }

    count += (exclTo - from);
    return count;
  }

  public int countInRange(int from, int exclTo, int minVal, int maxVal) {
    if (from >= exclTo || minVal > maxVal)
      return 0;

    int maxLimit = (1 << levels) - 1;
    if (maxVal > maxLimit)
      maxVal = maxLimit;
    if (minVal < 0)
      minVal = 0;
    if (minVal > maxVal)
      return 0;

    int targetMin = minVal - 1;
    boolean trackMin = targetMin >= 0;

    int countMax = 0, countMin = 0;
    int fMax = from, tMax = exclTo;
    int fMin = from, tMin = exclTo;

    for (int l = levels - 1; l >= 0; l--) {
      int[] p = pref[l];
      int zb = zeroBoundary[l];
      int bit = 1 << l;

      int zlMax = p[fMax];
      int zrMax = p[tMax];
      if ((maxVal & bit) == 0) {
        fMax = zlMax;
        tMax = zrMax;
      } else {
        countMax += (zrMax - zlMax);
        fMax = zb + fMax - zlMax;
        tMax = zb + tMax - zrMax;
      }

      if (trackMin) {
        int zlMin = p[fMin];
        int zrMin = p[tMin];
        if ((targetMin & bit) == 0) {
          fMin = zlMin;
          tMin = zrMin;
        } else {
          countMin += (zrMin - zlMin);
          fMin = zb + fMin - zlMin;
          tMin = zb + tMin - zrMin;
        }
      }
    }

    countMax += (tMax - fMax);
    if (trackMin) {
      countMin += (tMin - fMin);
    }

    return countMax - countMin;
  }
}
