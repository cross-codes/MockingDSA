package interfaces;

@FunctionalInterface
public interface IntegerXBiConsumer<U> {
  void accept(int t, U u);
}