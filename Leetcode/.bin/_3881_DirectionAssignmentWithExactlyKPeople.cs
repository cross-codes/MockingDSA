namespace _3881;

using System;
using System.Numerics;
using System.Runtime.CompilerServices;

public class Solution
{
    static int[] fact = new int[300001];
    static int[] invFact = new int[300001];
    const int MOD = (int)1e9 + 7;

    static Solution()
    {
        fact[0] = invFact[0] = 1;
        for (int i = 1; i < fact.Length; i++)
        {
            fact[i] = (int)(((long)fact[i - 1] * i) % MOD);
        }

        for (int i = 1; i < invFact.Length; i++)
        {
            invFact[i] = Algebra.CoprimeModInv(fact[i], MOD);
        }
    }

    // a people to the left, b people to the right
    // x + y = k where x <= a and y <= b
    // ans is (a, x) * (b, y) * 2 for all such x and y
    public int CountVisiblePeople(int n, int pos, int k)
    {

        long NCr(int n, int r)
        {
            if (r > n) return 0;
            // Console.WriteLine($"{n}, {r}");
            int numerator = fact[n];
            int denominator = (int)((invFact[n - r] * (long)invFact[r]) % MOD);
            return ((long)numerator * denominator) % MOD;
        }
        int a = pos, b = n - pos - 1;
        int gtot = 0;
        for (int x = 0; x <= a; x++)
        {
            int y = k - x;
            if (y <= b && y >= 0)
            {
                // Console.WriteLine($"{x}, {y}");
                long assignments = ((NCr(a, x) * NCr(b, y)) << 1) % MOD;
                gtot = (int)((assignments + (long)gtot) % MOD);
            }
        }

        return gtot;
    }
}

public static class Algebra
{
    private const double EPSILON = 1E-6;
    private const ulong MOD = 1000000007UL;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool IsEven(long a)
    {
        return (a & 1) == 0;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool IsOdd(long a)
    {
        return (a & 1) != 0;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool Chmin<T>(T a, T b) where T : INumber<T>
    {
        if (b < a)
        {
            a = b;
            return true;
        }
        else
        {
            return false;
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool Chmax<T>(T a, T b) where T : INumber<T>
    {
        if (a < b)
        {
            a = b;
            return true;
        }
        else
        {
            return false;
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static long Flip(long a)
    {
        return a ^ long.MinValue;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int ModPow(int n, int p, int m)
    {
        long result = 1L;
        for (long i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
        {
            if ((i & p) != 0)
            {
                result = result * j % m;
            }
        }
        return (int)result;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int CoprimeModInv(int n, int m)
    {
        return ModPow(n, m - 2, m);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static ulong Log2(ulong n)
    {
        return (ulong)BitOperations.Log2(n);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int CeilLog2(ulong n)
    {
        if (n <= 1)
            return 0;

        return BitOperations.Log2(n - 1) + 1;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool IsPrime(long n)
    {
        if (n < 2)
            return false;

        long x = 2L;
        while (x * x <= n)
        {
            if (n % x == 0)
                return false;
            x++;
        }

        return true;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool Equal(double a, double b)
    {
        return Math.Abs(a - b) < EPSILON;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool Equal0(double a)
    {
        return Math.Abs(a) < EPSILON;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static double[] SolveLinear(double a, double b, double c, double d, double e, double f)
    {
        double D = a * e - b * d;
        double Dx = c * e - b * f;
        double Dy = a * f - c * d;

        if (Equal0(D))
        {
            int size = Equal0(Dx) && Equal0(Dy) ? 1 : 0;
            return new double[size];
        }
        else
        {
            return new double[] { Dx / D, Dy / D };
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static double[] SolveQuadratic(double a, double b, double c)
    {
        double delta = b * b - 4 * a * c;
        if (Equal0(delta))
        {
            return new double[] { -b / (a * 2) };
        }
        else if (delta < 0)
        {
            return Array.Empty<double>();
        }
        else
        {
            double a2 = a * 2;
            double x = -b / a2;
            double y = Math.Sqrt(delta) / a2;

            return new double[] { x + y, x - y };
        }
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static bool SolveDiophantine(int a, int b, int c, out int x, out int y, out int g)
    {
        g = ExGCD(Math.Abs(a), Math.Abs(b), out x, out y);
        if (c % g != 0)
            return false;

        x *= c / g;
        y *= c / g;

        if (a < 0)
            x = -x;
        if (b < 0)
            y = -y;

        return true;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int GCD(int a, int b)
    {
        a = Math.Abs(a);
        b = Math.Abs(b);

        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }

        return a;
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static long LCM(int a, int b)
    {
        return ((long)a * b) / GCD(a, b);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private static int ExGCD(int a, int b, out int x, out int y)
    {
        if (b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }

        int x1, y1;
        int d = ExGCD(b, a % b, out x1, out y1);

        x = y1;
        y = x1 - y1 * (a / b);

        return d;
    }
}
