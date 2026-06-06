import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

class Solution {
  public int maximumSaleItems(int[][] items, long budget) {
    int[] freq = new int[100001];
    int n = items.length, mnc = Integer.MAX_VALUE;
    for (var item : items)
      mnc = Math.min(mnc, item[1]);

    List<Item> itemList = new ArrayList<Item>(n);
    for (int i = 0; i < n; i++) {
      if (items[i][1] <= mnc << 1) {
        itemList.add(new Item(i, items[i][1], items[i][0]));
      }
      freq[items[i][0]] += 1;
    }

    HashMap<Integer, Long> nfc = new HashMap<>(n);
    for (int i = 0; i < n; i++) {
      int factor = items[i][0];
      if (!nfc.containsKey(factor)) {
        long cnt = 0;
        for (int x = factor; x < 100001; x += factor)
          cnt += freq[x];

        nfc.put(factor, cnt - 1);
      }
    }

    itemList.sort((i1, i2) -> Long.compare(i1.cost(), i2.cost()));

    int cnt = 0;
    for (var e : itemList) {
      long buy = Math.min(budget / e.cost(), nfc.get(e.factor()));
      budget -= buy * e.cost();
      cnt += 2 * buy;
    }

    return (int) (cnt + (budget / itemList.getFirst().cost()));
  }

  private record Item(int idx, long cost, int factor) {
  };
}
