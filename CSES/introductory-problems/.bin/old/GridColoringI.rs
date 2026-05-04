use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

const COLORS: [char; 4] = ['A', 'B', 'C', 'D'];

fn next(color_left: char, color_up: char, color_curr: char) -> char
{
  for i in 0..4
  {
    let test_color: char = COLORS[i];
    if test_color != color_left
      && test_color != color_up
      && test_color != color_curr
    {
      return test_color;
    }
  }

  'W'
}

fn greedy_coloring(grid: &mut Vec<Vec<char>>, n: usize, m: usize) -> bool
{
  for y in 0..n
  {
    for x in 0..m
    {
      let color_left: char;
      let color_up: char;
      if y == 0
      {
        color_up = 'X';
      }
      else
      {
        color_up = grid[y - 1][x];
      }

      if x == 0
      {
        color_left = 'X';
      }
      else
      {
        color_left = grid[y][x - 1];
      }

      let next_color = next(color_left, color_up, grid[y][x]);
      if next_color == 'W'
      {
        return false;
      }
      else
      {
        grid[y][x] = next_color;
      }
    }
  }

  true
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
  let (n, m): (usize, usize) = (scanner.next(), scanner.next());
  let mut grid: Vec<Vec<char>> = (0..n)
    .map(|_| scanner.next::<String>().chars().collect())
    .collect();

  let res: bool = greedy_coloring(&mut grid, n, m);

  if !res
  {
    display!("IMPOSSIBLE\n");
    return;
  }

  for y in 0..n
  {
    for x in 0..m
    {
      display!(grid[y][x]);
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
  let stack_size: usize = 268435456;

  let handle: JoinHandle<()> = thread::Builder::new()
    .stack_size(stack_size)
    .spawn(|| {
      let stdin = io::stdin();
      let stdout = io::stdout();
      let mut scanner = Scanner::new(stdin.lock());
      let mut writer = BufWriter::new(stdout.lock());

      #[allow(unused_assignments)]
      let t: i32 = 1;

      (1..=t).for_each(|i| run(&mut scanner, &mut writer, i));
      writer.flush().unwrap();
    })
    .expect(&format!(
      "Failed to spawn thread. [STACK SIZE {} bytes]",
      stack_size
    ));

  handle.join().unwrap();
  Ok(())
}
