package year_2024.day2;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;

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
    int numberOfSafeLevels = 0;

    while (in.hasNextByte()) {
      ArrayList<String> stream = new ArrayList<>(
          Arrays.asList(new String(in.nextLine(), StandardCharsets.US_ASCII).split(" ")));
      if (this.isValidStream(stream, true))
        numberOfSafeLevels++;
    }

    out.append(numberOfSafeLevels);
  }

  @Override
  public boolean isValidStream(ArrayList<String> stream, boolean retryCheck) {
    int size = stream.size();
    if (size == 1)
      return true;

    boolean strictlyIncreasingStream = Integer.parseInt(stream.get(0)) < Integer.parseInt(stream.get(1));
    for (int i = 1; i < size; i++) {
      int first = Integer.parseInt(stream.get(i - 1));
      int second = Integer.parseInt(stream.get(i));

      if (strictlyIncreasingStream) {
        if (second - first > 3 || second - first <= 0) {
          if (retryCheck) {
            ArrayList<String> cloneWithFirstRemoved = new ArrayList<>(stream);
            cloneWithFirstRemoved.remove(i - 1);

            ArrayList<String> cloneWithSecondRemoved = new ArrayList<>(stream);
            cloneWithSecondRemoved.remove(i);

            ArrayList<String> cloneWithoutFirstElement = new ArrayList<>(stream);
            cloneWithoutFirstElement.remove(0);

            return isValidStream(cloneWithFirstRemoved, false)
                || isValidStream(cloneWithSecondRemoved, false)
                || isValidStream(cloneWithoutFirstElement, false);
          } else
            return false;
        }
      } else {
        if (first - second > 3 || first - second <= 0) {
          if (retryCheck) {
            ArrayList<String> cloneWithFirstRemoved = new ArrayList<>(stream);
            cloneWithFirstRemoved.remove(i - 1);

            ArrayList<String> cloneWithSecondRemoved = new ArrayList<>(stream);
            cloneWithSecondRemoved.remove(i);

            ArrayList<String> cloneWithoutFirstElement = new ArrayList<>(stream);
            cloneWithoutFirstElement.remove(0);

            return isValidStream(cloneWithFirstRemoved, false)
                || isValidStream(cloneWithSecondRemoved, false)
                || isValidStream(cloneWithoutFirstElement, false);
          } else
            return false;
        }
      }
    }

    return true;
  }

}

@MultipleInheritanceDisallowed(inheritor = Part2.class)
abstract strictfp class ModuleSignatures {
  abstract public boolean isValidStream(ArrayList<String> stream, boolean retryCheck);
}