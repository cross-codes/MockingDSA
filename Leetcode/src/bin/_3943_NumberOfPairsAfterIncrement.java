import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Solution {
  public int[] numberOfPairs(int[] a, int[] nums2, int[][] queries) {
    int n = nums2.length;

    int bsz = (int) Math.sqrt(n);
    int numBlocks = (n + bsz - 1) / bsz;

    long[] elements = Arrays.stream(nums2).mapToLong(i -> i).toArray();

    @SuppressWarnings("unchecked")
    Map<Long, Integer>[] blockMaps = new HashMap[numBlocks];
    for (int i = 0; i < numBlocks; i++)
      blockMaps[i] = new HashMap<>();

    long[] lazy = new long[numBlocks];
    for (int i = 0; i < n; i++) {
      int b = i / bsz;
      blockMaps[b].put(elements[i], blockMaps[b].getOrDefault(elements[i], 0) + 1);
    }

    Updater updater = (int b, int idx, long val) -> {
      long oldVal = elements[idx];
      int count = blockMaps[b].get(oldVal);
      if (count == 1) {
        blockMaps[b].remove(oldVal);
      } else {
        blockMaps[b].put(oldVal, count - 1);
      }
      elements[idx] += val;
      blockMaps[b].put(elements[idx], blockMaps[b].getOrDefault(elements[idx], 0) + 1);
    };

    List<Integer> answers = new ArrayList<>();
    for (int[] query : queries) {
      if (query[0] == 1) {
        int x = query[1], y = query[2];
        long val = query[3];

        int start = x / bsz;
        int end = y / bsz;
        if (start == end) {
          for (int i = x; i <= y; i++) {
            updater.update(start, i, val);
          }
        } else {
          int endOfStartBlock = (start + 1) * bsz - 1;
          for (int i = x; i <= endOfStartBlock; i++) {
            updater.update(start, i, val);
          }

          for (int b = start + 1; b < end; b++) {
            lazy[b] += val;
          }

          int startOfEndBlock = end * bsz;
          for (int i = startOfEndBlock; i <= y; i++) {
            updater.update(end, i, val);
          }
        }

      } else {
        int tot = query[1], cnt = 0;

        for (int e : a) {
          long target = (long) tot - e;
          for (int b = 0; b < numBlocks; b++) {
            long tgt = target - lazy[b];
            cnt += blockMaps[b].getOrDefault(tgt, 0);
          }
        }
        answers.add(cnt);
      }
    }

    return answers.stream().mapToInt(i -> i).toArray();
  }
}

@FunctionalInterface
interface Updater {
  void update(int b, int idx, long val);
}
