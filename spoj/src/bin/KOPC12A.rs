use std::cmp::min;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn f(n: usize, h: &Vec<i32>, c: &Vec<i32>, height: i32) -> i64
{
  let mut cost: i64 = 0;
  for i in 0..n
  {
    cost += (h[i] as i64 - height as i64).abs() * (c[i] as i64);
  }

  cost
}

fn unimodal_min(
  n: usize,
  h: &Vec<i32>,
  c: &Vec<i32>,
  mut l: i32,
  mut r: i32,
) -> i64
{
  while r - l >= 3
  {
    let m1: i32 = l + (r - l) / 3;
    let m2: i32 = r - (r - l) / 3;

    if f(n, h, c, m1) > f(n, h, c, m2)
    {
      l = m1;
    }
    else
    {
      r = m2;
    }
  }

  let mut min_val = i64::MAX;
  for i in l..=r
  {
    min_val = min(min_val, f(n, h, c, i) as i64);
  }

  min_val
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

  let n: usize = scanner.next();
  let h: Vec<i32> = (0..n).map(|_| scanner.next()).collect();
  let c: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  let h_min = h.iter().min().cloned().unwrap();
  let h_max = h.iter().max().cloned().unwrap();

  let res: i64 = unimodal_min(n, &h, &c, h_min, h_max);
  display!(res, "\n");
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
  let mut t: i32 = 1;
  t = scanner.next();

  (0..t).for_each(|_| run(&mut scanner, &mut writer));
  writer.flush().unwrap();

  Ok(())
}
