package util;

import java.util.Arrays;
import java.util.function.IntConsumer;

import interfaces.IntBiConsumer;
import primitives.Integer.IntegerArrayList;

class DensePrime {
  private int[] minima, powers;
  private boolean[] parity, squareFree;

  public IntegerArrayList primes;

  public DensePrime(int N) {
    this.minima = new int[N];
    this.powers = new int[N];

    this.parity = new boolean[N];
    this.squareFree = new boolean[N];
    this.primes = new IntegerArrayList(N >> 1);

    for (int i = 2; i < (N + 1) >> 1; i++) {
      int minimum, power;
      if (this.minima[i] == 0) {
        minimum = i;
        power = 1;
        this.parity[i] = this.squareFree[i] = true;
        this.primes.add(i);
      } else {
        minimum = this.minima[i];
        power = this.powers[i];
      }

      for (int e : this.primes) {
        int index = e * i;
        if (index < N) {
          this.minima[index] = e;
          this.parity[index] = !this.parity[i];
          if (e == minimum) {
            this.powers[index] = power + 1;
            break;
          } else {
            this.powers[index] = 1;
            this.squareFree[index] = this.squareFree[i];
          }
        } else {
          break;
        }
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2) {
      if (this.minima[i] == 0) {
        this.parity[i] = true;
        this.squareFree[i] = true;
      }
    }
  }

  boolean isSquareFree(int n) {
    return this.squareFree[n];
  }

  boolean getParity(int n) {
    return this.parity[n];
  }

  public int totient(int n) {
    int result = 1;
    while (minima[n] != 0) {
      int factor = 1;
      for (int i = 1; i < powers[n]; i++)
        factor *= minima[n];
      result *= factor * (minima[n] - 1);
      n /= factor * minima[n];
    }
    if (n != 1)
      result *= n - 1;
    return result;
  }

  public void forPrimeFactors(int n, IntConsumer consumer) {
    while (minima[n] != 0) {
      consumer.accept(minima[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      consumer.accept(n);
  }

  public void forPowers(int n, IntConsumer consumer) {
    while (minima[n] != 0) {
      consumer.accept(powers[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      consumer.accept(1);
  }

  public void forPrimeFactorsAndPowers(int n, IntBiConsumer biConsumer) {
    while (minima[n] != 0) {
      biConsumer.accept(minima[n], powers[n]);
      int factor = 1;
      for (int i = 0; i < powers[n]; i++)
        factor *= minima[n];
      n /= factor;
    }
    if (n != 1)
      biConsumer.accept(n, 1);
  }

  public void forFactors(int n, boolean includes1, boolean includesN, IntConsumer consumer) {
    if (n == 1) {
      if (includes1 && includesN)
        consumer.accept(1);
    } else {
      if (includes1)
        consumer.accept(1);
      IntegerArrayList primeFactors = new IntegerArrayList();
      IntegerArrayList powers = new IntegerArrayList();
      forPrimeFactorsAndPowers(n, (a, b) -> {
        primeFactors.add(a);
        powers.add(b);
      });
      int[] factors = primeFactors.toArray();
      int[] currentPowers = new int[factors.length];
      Arrays.fill(currentPowers, 1);
      int index = 0;
      while (true) {
        if (currentPowers[index] > powers.get(index))
          index++;
        else if (factors[index] == n) {
          if (includesN)
            consumer.accept(n);
          break;
        } else {
          consumer.accept(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * primeFactors.get(i);
          Arrays.fill(currentPowers, 0, index, 1);
          currentPowers[index]++;
          index = 0;
        }
      }
    }
  }
}
