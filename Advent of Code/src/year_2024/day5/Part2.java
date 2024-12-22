package year_2024.day5;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "cross", hostname = "inspiron", judge = "Advent of Code")
public class Part2 extends ModuleSignatures implements Runnable {

  private final StandardInputReader in = new StandardInputReader();
  private final StandardOutputWriter out = new StandardOutputWriter();
  @SuppressWarnings("unused")
  private final Debug dbg = Debug.getInstance();

  @Override
  public void run() {
    this.consolidateOutput();
    this.out.flush();
  }

  public static void main(String... args) {
    new Thread(null, new Part2(), "LaunchableDriver", 1048576L).start();
  }

  private void consolidateOutput() {
    HashMap<Integer, Page> knownPages = new HashMap<>();
    HashMap<Integer, HashSet<Integer>> pageBeforeMap = new HashMap<>();

    while (in.hasNextByte()) {
      String input = new String(in.nextLine(), StandardCharsets.US_ASCII);
      if (input.isEmpty())
        break;
      int[] nums = Stream.of(input.split("\\|")).mapToInt(Integer::parseInt).toArray();

      pageBeforeMap.computeIfAbsent(nums[0], k -> new HashSet<>()).add(nums[1]);

      if (knownPages.containsKey(nums[0])) {
        knownPages.get(nums[0]).addPageInFront(new Page(nums[1]));
      } else {
        Page newPage = new Page(nums[0]);
        newPage.addPageInFront(new Page(nums[1]));
        knownPages.put(nums[0], newPage);
      }
    }

    long result = 0L;
    while (in.hasNextByte()) {
      String input = new String(in.nextLine(), StandardCharsets.US_ASCII);
      int[] nums = Stream.of(input.split(",")).mapToInt(Integer::parseInt).toArray();
      if (!this.isValidSequence(nums, pageBeforeMap)) {
        ArrayList<Page> pages = IntStream.of(nums)
            .mapToObj(pageNum -> knownPages.getOrDefault(pageNum, new Page(pageNum)))
            .collect(Collectors.toCollection(ArrayList::new));
        Collections.sort(pages);
        result += pages.get(pages.size() / 2).pageNumber;
      }
    }

    out.append(result);
  }

  @Override
  public boolean isValidSequence(int[] sequence,
      HashMap<Integer, HashSet<Integer>> ruleset) {
    int n = sequence.length;

    for (int i = 0; i < n; i++) {
      int page = sequence[i];
      HashSet<Integer> pagesInFront = ruleset.get(page);
      if (pagesInFront == null)
        continue;
      for (int j = 0; j < i; j++) {
        if (pagesInFront.contains(sequence[j]))
          return false;
      }
      for (int j = i + 1; j < n; j++) {
        if (!pagesInFront.contains(sequence[j]))
          return false;
      }
    }

    return true;
  }

}

final class Page implements Comparable<Page> {

  final public int pageNumber;
  final private HashSet<Page> pagesInFront;

  public Page(int pageNumber) {
    this.pageNumber = pageNumber;
    this.pagesInFront = new HashSet<>();
  }

  public void addPageInFront(Page page) {
    this.pagesInFront.add(page);
  }

  @Override
  public int compareTo(Page otherPage) {
    if (this.pagesInFront.contains(otherPage))
      return -1;
    return 0;
  }

  @Override
  public boolean equals(Object o) {
    if (!(o instanceof Page))
      return false;
    Page equiv = (Page) o;
    return this.pageNumber == equiv.pageNumber;
  }

  @Override
  public int hashCode() {
    return Integer.hashCode(this.pageNumber);
  }

  @Override
  public String toString() {
    return String.valueOf(this.pageNumber);
  }
}

@MultipleInheritanceDisallowed(inheritor = Part2.class)
abstract strictfp class ModuleSignatures {
  abstract public boolean isValidSequence(int[] sequence,
      HashMap<Integer, HashSet<Integer>> ruleSet);
}