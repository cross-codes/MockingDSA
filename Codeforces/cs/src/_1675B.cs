using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1675B
{
    public class _1675B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1675B.txt"), false);
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
            long gcnt = 0;
            for (int i = n - 2; i >= 0; i--) {
                if (a[i] >= a[i + 1]) {
                    while (a[i] != 0 && a[i] >= a[i + 1]) {
                        a[i] /= 2;
                        gcnt += 1;
                    }

                    if (a[i] == 0 && a[i] >= a[i + 1]) {
                        output.Append(-1).AppendNewLine();
                        return;
                    }
                }
            }

            output.Append(gcnt).AppendNewLine();
        }
    }
}
