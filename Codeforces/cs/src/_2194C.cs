using System.IO;
using System.Text;
using System.Linq;
using System.Runtime.CompilerServices;
using Evermore.IO;
using System.Collections.Generic;

namespace _2194C
{
    internal class _2194C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new StandardInputReader();
        private static readonly StandardOutputWriter output = new StandardOutputWriter();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2194C.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int n = input.NextInt(), k = input.NextInt();
            var positions = Enumerable.Range(0, 26)
                                      .Select(_ => new HashSet<int>())
                                      .ToArray();

            for (int i = 0; i < k; i++)
            {
                string tape = input.NextStr();
                for (int j = 1; j <= tape.Length; j++)
                {
                    positions[tape[j - 1] - 'a'].Add(j);
                }
            }


            List<int> factors = new List<int>();
            for (int i = 1; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    factors.Add(i);
                    if (i != n / i)
                    {
                        factors.Add(n / i);
                    }
                }
            }
            factors.Sort();

            string TryCheckInformativity(int d)
            {
                char TryCheckSequence(int i)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        bool found = true;
                        for (int k = i; k <= n; k += d)
                        {
                            if (!positions[j].Contains(k))
                            {
                                found = false;
                                break;
                            }
                        }

                        if (found)
                        {
                            return (char)(j + 'a');
                        }
                    }

                    return '$';
                }

                StringBuilder sb = new StringBuilder();
                for (int i = 1; i <= d; i++)
                {
                    char r = TryCheckSequence(i);
                    if (r != '$')
                    {
                        sb.Append(r);
                        continue;
                    }
                    else
                    {
                        return "";
                    }
                }

                return sb.ToString();
            }

            foreach (int f in factors)
            {
                string possible = TryCheckInformativity(f);
                if (possible.Length == f)
                {
                    for (int i = 0; i < n / f; i++)
                    {
                        output.Append(possible);
                    }
                    output.AppendNewLine();
                    return;
                }
            }
        }
    }
}
