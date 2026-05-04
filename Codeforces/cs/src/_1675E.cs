using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;
using Evermore.Collections.Ranged;

namespace _1675E
{
    public class _1675E
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1675E.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (n, k) = (input.NextInt(), input.NextInt());
            string s = input.NextStr();
            char[] ch = s.ToCharArray();

            Func<char, char, char> mx = (char a, char b) =>
            {
                return (char)Math.Max(a, b);
            };

            IdempotentSparseTable<char> table = new(ch, mx);

            void GPRep1(char what, char with)
            {
                for (int i = 0; i < n; i++)
                {
                    if (ch[i] <= what)
                    {
                        ch[i] = with;
                    }
                }
            }

            void GPRep2(char what, char with)
            {
                for (int i = 0; i < n; i++)
                {
                    if (ch[i] >= with && ch[i] <= what)
                    {
                        ch[i] = with;
                    }
                }
            }
            (char, int) FindLargestWithinBounds(int s, int k, int indiff)
            {
                int L = s, R = n + 1;

                while (R - L > 1)
                {
                    int M = (L + R) >>> 1;

                    char d = table.RangeQuery(s, M);

                    if (d - 'a' <= k)
                    {
                        L = M;
                    }
                    else
                    {
                        R = M;
                    }
                }

                char mx = table.RangeQuery(s, L);
                return (mx, mx - 'a');
            }

            for (int i = 0; i < n; i++)
            {
                char c = ch[i];
                int diff = (int)(c - 'a');
                if (diff == 0) continue;
                if (diff <= k)
                {
                    var (d, del) = FindLargestWithinBounds(i, k, diff);
                    GPRep1(d, 'a');
                    k -= del;
                    table = new IdempotentSparseTable<char>(ch, mx);
                }
                else
                {
                    GPRep2(c, (char)((int)c - k));
                    k = 0;
                    break;
                }
            }

            string res = new(ch);
            output.Append(res).AppendNewLine();
        }
    }
}
