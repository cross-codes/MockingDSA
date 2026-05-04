using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1934A
{
    public class _1934A
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1934A.txt"), false);
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
            Array.Sort(a);
            long ai = a[0], aj = a[n - 1], ak = a[1], al = a[n - 2];
            output.Append(Math.Abs(ai - aj) + Math.Abs(aj - ak) + Math.Abs(ak - al) + Math.Abs(al - ai)).AppendNewLine();
        }
    }
}
