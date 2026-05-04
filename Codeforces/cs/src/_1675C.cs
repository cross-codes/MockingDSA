using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1675C
{
    public class _1675C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1675C.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            string s = input.NextStr();
            int n = s.Length;
            bool[] behindZero = new bool[n], aheadOne = new bool[n];
            bool seeZero = false;
            for (int i = 0; i < n; i++) {
                behindZero[i] = seeZero;
                if (s[i] == '0') {
                    seeZero = true;
                }
            }

            bool seeOne = false;
            for (int i = n - 1; i >= 0; i--) {
                aheadOne[i] = seeOne;
                if (s[i] == '1') {
                    seeOne = true;
                }
            }

            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (!(behindZero[i] || aheadOne[i])) {
                    cnt += 1;
                }
            }

            output.Append(cnt).AppendNewLine();
        }
    }
}
