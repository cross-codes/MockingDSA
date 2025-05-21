use std::cmp::min;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn f(n: usize, h: &Vec<i32>, c: &Vec<i32>, height: f64) -> f64
{
  let mut cost: f64 = 0.0;
  for i in 0..n
  {
    cost += (h[i] as f64 - height).abs() * (c[i] as f64);
  }

  cost
}

fn unimodal_min(
  n: usize,
  h: &Vec<i32>,
  c: &Vec<i32>,
  mut l: f64,
  mut r: f64,
) -> i64
{
  while r - l >= 3.0
  {
    let m1: f64 = l + (r - l) / 3.0;
    let m2: f64 = r - (r - l) / 3.0;

    if f(n, h, c, m1) > f(n, h, c, m2)
    {
      l = m1;
    }
    else
    {
      r = m2;
    }
  }

  let lower_lim: i64 = l.floor() as i64;
  let upper_lim: i64 = r.ceil() as i64;

  let mut min_val = i64::MAX;

  for i in lower_lim..=upper_lim
  {
    min_val = min(min_val, f(n, h, c, i as f64) as i64);
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

  let h_min = *h.iter().min().unwrap() as f64;
  let h_max = *h.iter().max().unwrap() as f64;

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
