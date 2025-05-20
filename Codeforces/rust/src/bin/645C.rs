use std::cmp::{max, min};
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn predicate(
  s: &Vec<char>,
  num_zeroes_upto: &Vec<i32>,
  pos: i32,
  k: i32,
  n: usize,
) -> bool
{
  for i in 1..=n
  {
    let left_end: i32 = max(1i32, i as i32 - pos);
    let right_end: i32 = min(n as i32, i as i32 + pos);
    if s[i] == '0'
      && num_zeroes_upto[right_end as usize]
        - num_zeroes_upto[(left_end - 1) as usize]
        >= k + 1
    {
      return true;
    }
  }

  false
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
  let k: i32 = scanner.next();
  let mut str: String = scanner.next();
  str.insert_str(0, "$");

  let s: Vec<char> = str.chars().collect();
  let mut num_zeroes_upto: Vec<i32> = vec![0; n + 1];
  for i in 1..=n
  {
    num_zeroes_upto[i] = num_zeroes_upto[i - 1];
    if s[i] == '0'
    {
      num_zeroes_upto[i] += 1;
    }
  }

  let mut l: i32 = -1;
  let mut r: i32 = n as i32;
  while r - l > 1
  {
    let m: i32 = l + ((r - l) >> 1);
    if predicate(&s, &num_zeroes_upto, m, k, n)
    {
      r = m;
    }
    else
    {
      l = m;
    }
  }

  display!(r, "\n");
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
