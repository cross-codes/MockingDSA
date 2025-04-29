use std::cmp::max;
use std::io::{self, BufRead, BufWriter, Write};

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
)
{
  macro_rules! print {
        () => {
            writeln!(writer).unwrap();
        };
        ($arg:expr) => {
            write!(writer, "{}", $arg).unwrap();
        };
        ($arg:expr, $($rest:expr),*) => {
            write!(writer, "{}", $arg).unwrap();
            print!($($rest),*);
        };
    }

  let n: usize = scanner.next();
  let mut a: Vec<i32> = vec![0; n];
  let mut maximum: Vec<i32> = vec![i32::MIN; n];

  let mut current_max: i32 = i32::MIN;
  for i in 0..n
  {
    let num: i32 = scanner.next();
    current_max = max(current_max, num);
    maximum[i] = current_max;
    a[i] = num;
  }

  let mut suffix_sum: Vec<i64> = vec![0; n + 1];
  for i in (0..n).rev()
  {
    suffix_sum[i] = suffix_sum[i + 1] + (a[i] as i64);
  }

  for i in 0..n - 1
  {
    print!(suffix_sum[n - i] + maximum[n - i - 1] as i64, " ");
  }

  print!(suffix_sum[0], "\n");
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

fn main()
{
  let stdin = io::stdin();
  let stdout = io::stdout();
  let mut scanner = Scanner::new(stdin.lock());
  let mut writer = BufWriter::new(stdout.lock());

  #[allow(unused_assignments)]
  let mut t: i32 = 1;
  t = scanner.next();

  for _ in 0..t
  {
    run(&mut scanner, &mut writer);
  }

  writer.flush().unwrap();
}
