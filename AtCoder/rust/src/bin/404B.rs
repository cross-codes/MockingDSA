use std::cmp::min;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn transpose_and_reverse(v: &mut Vec<Vec<char>>) -> Vec<Vec<char>>
{
  let rows = v.len();
  let cols = v[0].len();

  let mut transposed: Vec<Vec<char>> = (0..cols)
    .map(|col| (0..rows).map(|row| v[row][col]).collect())
    .collect();

  for row in transposed.iter_mut()
  {
    row.reverse();
  }

  transposed
}

fn difference(u: &Vec<Vec<char>>, v: &Vec<Vec<char>>) -> i32
{
  let rows = u.len();
  let cols = u[0].len();

  let mut diff: i32 = 0;
  for y in 0..rows
  {
    for x in 0..cols
    {
      if u[y][x] != v[y][x]
      {
        diff += 1;
      }
    }
  }

  diff
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

  let mut u: Vec<Vec<char>> = Vec::new();
  let mut v: Vec<Vec<char>> = Vec::new();

  for _ in 0..n
  {
    let row: String = scanner.next();
    let chars: Vec<char> = row.chars().collect();
    u.push(chars);
  }

  for _ in 0..n
  {
    let row: String = scanner.next();
    let chars: Vec<char> = row.chars().collect();
    v.push(chars);
  }

  let mut min_diff: i32 = difference(&u, &v);
  for i in 1..4
  {
    u = transpose_and_reverse(&mut u);
    min_diff = min(min_diff, i + difference(&u, &v));
  }

  display!(min_diff, "\n");
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
