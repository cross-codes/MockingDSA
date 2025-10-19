use std::collections::BTreeMap;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::ops::Bound::{Excluded, Unbounded};

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
  let mut sizes: BTreeMap<i32, i64> = BTreeMap::new();

  for _ in 0..n
  {
    let k: i32 = scanner.next();
    let upper_bound = sizes.range((Excluded(&k), Unbounded)).next();
    match upper_bound
    {
      Some((&key, &value)) =>
      {
        if value > 1
        {
          sizes.insert(key, value - 1);
        }
        else
        {
          sizes.remove(&key);
        }

        *sizes.entry(k).or_insert(0) += 1;
      }

      None =>
      {
        *sizes.entry(k).or_insert(0) += 1;
      }
    }
  }

  display!(sizes.values().sum::<i64>(), "\n");
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

  for _ in 0..t
  {
    run(&mut scanner, &mut writer);
  }

  writer.flush().unwrap();

  Ok(())
}
