package interfaces;

@FunctionalInterface
public interface IntXBiConsumer<U> {
  void accept(int t, U u);
}
