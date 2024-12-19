package year_2024.day1;

import java.util.PriorityQueue;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "cross", hostname = "inspiron", judge = "Advent of Code")
public class Part1 extends ModuleSignatures implements Runnable {

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
    new Thread(null, new Part1(), "LaunchableDriver", 1048576L).start();
  }

  private void consolidateOutput() {
    final PriorityQueue<Integer> queue1 = new PriorityQueue<>();
    final PriorityQueue<Integer> queue2 = new PriorityQueue<>();

    while (in.hasNextByte()) {
      queue1.add(in.nextInt());
      queue2.add(in.nextInt());
    }

    long distance = 0L;
    while (!queue1.isEmpty())
      distance += Math.abs(queue1.poll() - queue2.poll());

    out.append(distance);
  }

}

@MultipleInheritanceDisallowed(inheritor = Part1.class)
abstract strictfp class ModuleSignatures {
}