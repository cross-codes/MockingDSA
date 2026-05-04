using System.IO;
using System.Runtime.CompilerServices;
using Evermore.IO;
using Evermore.Collections.Ranged;

namespace _1933E
{
    internal class _1933E
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1933E.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int n = input.NextInt();
            int[] a = input.ReadIntegerArray(n);

            StaticPrefixSum<int> prefix = new(a);

            long f(long k, int u)
            {
                return k * u - (k * (k - 1) >> 1);
            }

            int UnimodalMax(int l, int u)
            {
                int L = l;
                int R = n - 1;
                while (R - L >= 3)
                {
                    int m1 = L + (R - L) / 3;
                    int m2 = R - (R - L) / 3;
                    if (f(prefix.RangeSum(l, m1 + 1), u) < f(prefix.RangeSum(l, m2 + 1), u))
                    {
                        L = m1;
                    }
                    else
                    {
                        R = m2;
                    }
                }

                long mx = f(prefix.RangeSum(l, L + 1), u);
                int best = L;
                for (int i = L; i <= R; i++)
                {
                    long val = f(prefix.RangeSum(l, i + 1), u);
                    if (val > mx)
                    {
                        best = i;
                        mx = val;
                    }
                }

                return best;
            }

            int q = input.NextInt();
            for (int i = 0; i < q; i++)
            {
                int l = input.NextInt(), u = input.NextInt();
                output.Append(1 + UnimodalMax(l - 1, u)).Append(" ");
            }

            output.AppendNewLine();
        }
    }
}
