use std::collections::BTreeMap;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::ops::Bound::{Included, Unbounded};

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
  let m: usize = scanner.next();

  let mut tickets: BTreeMap<i32, i32> = BTreeMap::new();
  for _ in 0..n
  {
    let h: i32 = scanner.next();
    tickets
      .entry(h)
      .and_modify(|value| *value += 1)
      .or_insert(1);
  }

  for _ in 0..m
  {
    let t: i32 = scanner.next();
    let lower_bound = tickets.range((Unbounded, Included(t))).next_back();

    match lower_bound
    {
      Some((&key, &value)) =>
      {
        print!(key, "\n");

        if value > 1
        {
          if let Some(v) = tickets.get_mut(&key)
          {
            *v -= 1;
          }
        }
        else
        {
          tickets.remove(&key);
        }
      }

      None =>
      {
        print!(-1, "\n");
      }
    }
  }
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
