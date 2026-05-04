using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace B
{
    public class B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "B.txt"), false);
            int t = input.NextInt();
            List<long> T = new(50000);
            for (long i = 0; (i * (i + 1) / 2) <= 1e9; i++)
            {
                T.Add(i * (i + 1) / 2);
            }

            int[] coins = { 1, 3, 6, 10, 15 };
            long[] mnw = new long[100];
            mnw[0] = 0;
            for (int i = 1; i < 100; i++)
            {
                mnw[i] = int.MaxValue;
                foreach (int coin in coins)
                {
                    if (i - coin >= 0 && mnw[i - coin] != int.MaxValue)
                    {
                        mnw[i] = Math.Min(mnw[i], mnw[i - coin] + 1);
                    }
                }
            }
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case, T, mnw);
            }
            output.Flush();
        }


        private static void SolveCase(int _case, List<long> T, long[] mnw)
        {
            int n = input.NextInt();

            long GetMinCoins(long x)
            {
                if (x < 100) return mnw[(int)x];
                long a = (x - 80) / 15;
                long rem = x - (a * 15);
                return a + mnw[(int)rem];
            }

            output.Append(GetMinCoins(n)).AppendNewLine();
        }
    }
}
