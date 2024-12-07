package neetcode.practice.Arrays;

import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class Solution {
  public int[] topKFrequent(int[] nums, int k) {
    HashMap<Integer, Integer> map = new HashMap<>();
    for (int i = 0; i < nums.length; i++)
      map.put(nums[i], map.getOrDefault(nums[i], 0) + 1);

    PriorityQueue<FrequencyAwareInteger> queue = new PriorityQueue<>();
    int currentSize = 0;

    for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
      int num = entry.getKey(), freq = entry.getValue();
      FrequencyAwareInteger i = new FrequencyAwareInteger(num, freq);
      if (currentSize != k) {
        queue.add(i);
        currentSize++;
      } else if (i.frequency > queue.peek().frequency) {
        queue.poll();
        queue.add(i);
      }
    }

    return queue.stream().mapToInt((x) -> x.value).toArray();
  }
}

class FrequencyAwareInteger implements Comparable<FrequencyAwareInteger> {
  public int value;
  public int frequency;

  public FrequencyAwareInteger(int value, int frequency) {
    this.value = value;
    this.frequency = frequency;
  }

  @Override
  public int compareTo(FrequencyAwareInteger i) {
    return Integer.compare(this.frequency, i.frequency);
  }
}