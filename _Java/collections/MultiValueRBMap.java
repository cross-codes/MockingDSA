package collections;

import java.util.Comparator;
import java.util.TreeMap;
import java.util.TreeSet;

public class MultiValueRBMap extends TreeMap<Integer, TreeSet<Integer>> {

  public MultiValueRBMap() {
    super();
  }

  public MultiValueRBMap(Comparator<? super Integer> comp) {
    super(comp);
  }

  public boolean removeValueFromKey(Integer key, Integer value) {
    if (key == null)
      return false;

    TreeSet<Integer> values = this.get(key);
    if (values != null && values.remove(value)) {
      if (values.isEmpty())
        this.remove(key);
      return true;
    }

    return false;
  }

  public boolean addValueToKeyOrDefault(Integer key, Integer value) {
    if (key == null)
      return false;

    this.computeIfAbsent(key, k -> new TreeSet<>()).add(value);
    return true;
  }
}