use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn f(x: f64, a: &Vec<i32>) -> f64
{
  let mut current_pos_sum: f64 = 0.0;
  let mut current_neg_sum: f64 = 0.0;
  let mut best_pos_sum: f64 = f64::MIN;
  let mut best_neg_sum: f64 = f64::MAX;

  for e in a
  {
    let ef: f64 = *e as f64;
    current_pos_sum = f64::max(current_pos_sum - x + ef, ef - x);
    best_pos_sum = f64::max(best_pos_sum, current_pos_sum);

    current_neg_sum = f64::min(current_neg_sum - x + ef, ef - x);
    best_neg_sum = f64::min(best_neg_sum, current_neg_sum);
  }

  f64::max(best_pos_sum, best_neg_sum.abs())
}

fn unimodal_min(a: &Vec<i32>, mut l: f64, mut r: f64) -> f64
{
  let epsilon: f64 = 5e-12;
  while r - l > epsilon
  {
    let m1: f64 = l + (r - l) / 3.0;
    let m2: f64 = r - (r - l) / 3.0;

    if f(m1, a) > f(m2, a)
    {
      l = m1;
    }
    else
    {
      r = m2;
    }
  }

  f((l + r) / 2.0, a)
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
  let a: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  let min_a = a.iter().min().cloned().unwrap() as f64;
  let max_a = a.iter().max().cloned().unwrap() as f64;

  display!(unimodal_min(&a, min_a, max_a), "\n");
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
