class Solution {
  public int earliestFinishTime(int[] landStartTime, int[] landDuration, int[] waterStartTime, int[] waterDuration) {
    int best = Integer.MAX_VALUE;
    for (int l = 0; l < landStartTime.length; l++) {
      for (int w = 0; w < waterStartTime.length; w++) {
        int landEnd = landStartTime[l] + landDuration[l];
        best = Math.min(best, Math.max(landEnd, waterStartTime[w]) + waterDuration[w]);
      }
    }

    for (int w = 0; w < waterStartTime.length; w++) {
      for (int l = 0; l < landStartTime.length; l++) {
        int waterEnd = waterStartTime[w] + waterDuration[w];
        best = Math.min(best, Math.max(waterEnd, landStartTime[l]) + landDuration[l]);
      }
    }

    return best;
  }
}
