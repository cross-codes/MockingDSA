use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn num_pillows(n: i64, k: i64, x: i64) -> i64
{
  let mut res: i64 = n + x;
  if x > k
  {
    res += (k - 1) * x - ((k * (k - 1)) >> 1);
  }
  else
  {
    res += ((x - 1) * x) >> 1;
  }

  if x > n - k
  {
    res += (n - k) * x - (((n - k) * (n - k + 1)) >> 1);
  }
  else
  {
    res += ((x - 1) * x) >> 1;
  }

  res
}

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
)
{
  macro_rules! display {
        () => {
            writeln!(writer).unwrap();
        };
        ($arg:expr) => {
            write!(writer, "{}", $arg).unwrap();
        };
        ($arg:expr, $($rest:expr),*) => {
            write!(writer, "{}", $arg).unwrap();
            display!($($rest),*);
        };
    }

  let n: i64 = scanner.next();
  let m: i64 = scanner.next();
  let k: i64 = scanner.next();

  let mut l: i64 = -1;
  let mut r: i64 = m - n + 1;
  while r - l > 1
  {
    let x: i64 = l + ((r - l) >> 1);
    if m < num_pillows(n, k, x)
    {
      r = x;
    }
    else
    {
      l = x;
    }
  }

  display!(l + 1, "\n");
}

struct Scanner<B>
{
  reader: B,
  buffer: Vec<String>,
  pos: usize,
}

impl<B: BufRead> Scanner<B>
{
  fn new(reader: B) -> Self
  {
    Self {
      reader,
      buffer: Vec::new(),
      pos: 0,
    }
  }

  fn next<T: std::str::FromStr>(&mut self) -> T
  where
    T::Err: std::fmt::Debug,
  {
    self.ensure_buffered();
    let val = self.buffer[self.pos].parse().unwrap();
    self.pos += 1;
    val
  }

  fn ensure_buffered(&mut self)
  {
    if self.pos >= self.buffer.len()
    {
      let mut line = String::new();
      self.reader.read_line(&mut line).unwrap();
      self.buffer = line.split_whitespace().map(|s| s.to_owned()).collect();
      self.pos = 0;
    }
  }
}

fn main() -> Result<(), Box<dyn Error>>
{
  let stdin = io::stdin();
  let stdout = io::stdout();
  let mut scanner = Scanner::new(stdin.lock());
  let mut writer = BufWriter::new(stdout.lock());

  #[allow(unused_assignments)]
  let t: i32 = 1;

  (0..t).for_each(|_| run(&mut scanner, &mut writer));
  writer.flush().unwrap();

  Ok(())
}
