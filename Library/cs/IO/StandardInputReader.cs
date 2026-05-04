using System;
using System.IO;
using System.Text;

namespace Evermore.IO;

public class StandardInputReader
{
    private readonly byte[] buffer;
    private int pos;

    public StandardInputReader()
    {
        try
        {
            this.pos = 0;
            using (var ms = new MemoryStream())
            {
                using (var stdin = Console.OpenStandardInput())
                {
                    stdin.CopyTo(ms);
                }
                byte[] inputBytes = ms.ToArray();
                this.buffer = new byte[inputBytes.Length + 1];
                Array.Copy(inputBytes, this.buffer, inputBytes.Length);
                this.buffer[this.buffer.Length - 1] = (byte)'\n';
            }
        }
        catch (Exception ex)
        {
            throw new Exception("Failed to read stdin", ex);
        }
    }

    public string NextStr()
    {
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b != ' ' && b != '\n' && b != '\r')
            {
                this.pos--;
                break;
            }
        }

        int from = this.pos;

        while (true)
        {
            byte b = this.buffer[this.pos++];

            if (b == '\n' || b == '\r' || b == ' ')
            {
                int length = this.pos - from - 1;
                string str = Encoding.UTF8.GetString(this.buffer, from, length);
                if (b == '\r' && this.pos < this.buffer.Length && this.buffer[this.pos] == '\n')
                {
                    this.pos++;
                }

                return str;
            }
        }
    }

    public byte NextByte()
    {
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b != ' ' && b != '\n' && b != '\r')
                return b;
        }
    }

    public int NextInt()
    {
        int n;
        bool positive;
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b == '-')
            {
                positive = false;
                n = this.buffer[this.pos++] - '0';
                break;
            }
            else if (b >= '0' && b <= '9')
            {
                positive = true;
                n = b - '0';
                break;
            }
        }
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b >= '0' && b <= '9')
                n = n * 10 + b - '0';
            else
                return positive ? n : -n;
        }
    }

    public long NextLong()
    {
        long n;
        bool positive;
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b == '-')
            {
                positive = false;
                n = this.buffer[this.pos++] - '0';
                break;
            }
            else if (b >= '0' && b <= '9')
            {
                positive = true;
                n = b - '0';
                break;
            }
        }
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b >= '0' && b <= '9')
                n = n * 10 + b - '0';
            else
                return positive ? n : -n;
        }
    }

    public double NextDouble()
    {
        long n;
        bool positive;
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b == '-')
            {
                positive = false;
                n = this.buffer[this.pos++] - '0';
                break;
            }
            else if (b >= '0' && b <= '9')
            {
                positive = true;
                n = b - '0';
                break;
            }
        }
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b >= '0' && b <= '9')
                n = n * 10 + b - '0';
            else if (b == '.')
                break;
            else
                return positive ? n : -n;
        }
        long m = 0;
        long o = 1;
        while (true)
        {
            byte b = this.buffer[this.pos++];
            if (b >= '0' && b <= '9')
            {
                m = m * 10 + b - '0';
                o *= 10;
            }
            else
            {
                double d = n + (double)m / o;
                return positive ? d : -d;
            }
        }
    }

    public int[] ReadIntegerArray(int n)
    {
        int[] a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = NextInt();
        return a;
    }

    public long[] ReadLongArray(int n)
    {
        long[] a = new long[n];
        for (int i = 0; i < n; i++)
            a[i] = NextLong();
        return a;
    }

    public bool HasNextByte()
    {
        return this.pos < this.buffer.Length - 1;
    }
}

