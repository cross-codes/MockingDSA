package year_2024.day1;

import java.util.HashMap;
import java.util.Map;

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
    HashMap<Integer, Integer> intToFrequency1 = new HashMap<>();
    HashMap<Integer, Integer> intToFrequency2 = new HashMap<>();

    while (in.hasNextByte()) {
      int num = in.nextInt();
      intToFrequency1.put(num, intToFrequency1.getOrDefault(num, 0) + 1);
      num = in.nextInt();
      intToFrequency2.put(num, intToFrequency2.getOrDefault(num, 0) + 1);
    }

    long similarityScore = 0;
    for (Map.Entry<Integer, Integer> entry : intToFrequency1.entrySet()) {
      int number = entry.getKey(), occurencesInFirstList = entry.getValue();
      int occurencesInSecondList = intToFrequency2.getOrDefault(number, 0);
      similarityScore += (number * occurencesInSecondList) * occurencesInFirstList;
    }

    out.append(similarityScore);
  }

}

@MultipleInheritanceDisallowed(inheritor = Part2.class)
abstract strictfp class ModuleSignatures {
}