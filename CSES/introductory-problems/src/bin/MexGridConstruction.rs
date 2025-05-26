use std::cmp::max;
use std::collections::HashSet;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn mex_row_col(grid: &Vec<Vec<i32>>, y: usize, x: usize) -> i32
{
  let mut set: HashSet<i32> = HashSet::new();
  let mut max_num: i32 = i32::MIN;
  for row in 0..y
  {
    set.insert(grid[row][x]);
    max_num = max(max_num, grid[row][x]);
  }

  for col in 0..x
  {
    set.insert(grid[y][col]);
    max_num = max(max_num, grid[y][col]);
  }

  if max_num < 0
  {
    return 0;
  }

  for i in 0..=max_num
  {
    if !set.contains(&i)
    {
      return i;
    }
  }

  max_num + 1
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
  let mut mex_grid: Vec<Vec<i32>> = vec![vec![-1; n]; n];

  for y in 0..n
  {
    for x in 0..n
    {
      mex_grid[y][x] = mex_row_col(&mex_grid, y, x);
      display!(mex_grid[y][x], " ");
    }

    display!("\n");
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

  (0..t).for_each(|_| run(&mut scanner, &mut writer));
  writer.flush().unwrap();

  Ok(())
}
