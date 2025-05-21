use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn f(
  t: f64,
  rai: (f64, f64),
  raf: (f64, f64),
  rbi: (f64, f64),
  rbf: (f64, f64),
) -> f64
{
  let xac: f64 = rai.0 + (raf.0 - rai.0) * t;
  let yac: f64 = rai.1 + (raf.1 - rai.1) * t;

  let xbc: f64 = rbi.0 + (rbf.0 - rbi.0) * t;
  let ybc: f64 = rbi.1 + (rbf.1 - rbi.1) * t;

  f64::sqrt((xac - xbc).powi(2) + (yac - ybc).powi(2))
}

fn unimodal_min(
  rai: (f64, f64),
  raf: (f64, f64),
  rbi: (f64, f64),
  rbf: (f64, f64),
  mut l: f64,
  mut r: f64,
) -> f64
{
  let epsilon: f64 = 5e-12;
  while r - l > epsilon
  {
    let m1: f64 = l + (r - l) / 3.0;
    let m2: f64 = r - (r - l) / 3.0;

    if f(m1, rai, raf, rbi, rbf) > f(m2, rai, raf, rbi, rbf)
    {
      l = m1;
    }
    else
    {
      r = m2;
    }
  }

  f((l + r) / 2.0, rai, raf, rbi, rbf)
}

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
  _case: i32,
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

  let rai: (f64, f64) = (scanner.next(), scanner.next());
  let raf: (f64, f64) = (scanner.next(), scanner.next());
  let rbi: (f64, f64) = (scanner.next(), scanner.next());
  let rbf: (f64, f64) = (scanner.next(), scanner.next());

  display!(
    "Case ",
    _case,
    ": ",
    unimodal_min(rai, raf, rbi, rbf, 0.0f64, 1.0f64),
    "\n"
  );
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

  (1..=t).for_each(|i| run(&mut scanner, &mut writer, i));
  writer.flush().unwrap();

  Ok(())
}
