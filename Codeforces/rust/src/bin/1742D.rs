use std::cmp::max;
use std::collections::HashMap;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn gcd(a: i32, b: i32) -> i32
{
  if b == 0
  {
    a
  }
  else
  {
    gcd(b, a % b)
  }
}

fn brute_force(distinct: &HashMap<i32, isize>) -> isize
{
  let mut max_sum: isize = -1;

  for (key, value) in distinct.iter()
  {
    for (other_key, other_value) in distinct.iter()
    {
      if gcd(*key, *other_key) == 1
      {
        max_sum = max(max_sum, value + other_value);
      }
    }
  }

  max_sum
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

  let n: isize = scanner.next();
  let mut distinct: HashMap<i32, isize> = HashMap::new();

  for i in 1..n + 1
  {
    let num: i32 = scanner.next();
    distinct.insert(num, i);
  }

  display!(brute_force(&distinct), "\n");
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

  for _ in 0..t
  {
    run(&mut scanner, &mut writer);
  }

  writer.flush().unwrap();

  Ok(())
}
