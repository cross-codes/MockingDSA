use std::io::{self, BufRead, BufWriter, Write};

const N: usize = 7;

#[derive(PartialEq)]
enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE,
}

fn in_bounds(x: usize, y: usize) -> bool
{
  return (x >= 1) && (y >= 1) && (x <= N) && (y <= N);
}

fn can_go(
  dir: &Direction,
  x: usize,
  y: usize,
  visited: &mut [[bool; N + 1]; N + 1],
) -> bool
{
  match dir
  {
    Direction::UP => in_bounds(x, y - 1) && !visited[y - 1][x],
    Direction::RIGHT => in_bounds(x + 1, y) && !visited[y][x + 1],
    Direction::DOWN => in_bounds(x, y + 1) && !visited[y + 1][x],
    Direction::LEFT => in_bounds(x - 1, y) && !visited[y][x - 1],
    _ => false,
  }
}

fn search(
  x: usize,
  y: usize,
  idx: usize,
  seq: &mut Vec<char>,
  dir: Direction,
  cnt: &mut u32,
  visited: &mut [[bool; N + 1]; N + 1],
)
{
  if idx == N * N - 1 || x == 1 && y == N
  {
    if idx == N * N - 1 && x == 1 && y == N
    {
      *cnt += 1;
    }

    return;
  }

  if !can_go(&dir, x, y, visited)
  {
    if dir == Direction::UP || dir == Direction::DOWN
    {
      if can_go(&Direction::RIGHT, x, y, visited)
        && can_go(&Direction::LEFT, x, y, visited)
      {
        return;
      }
    }
    else if dir == Direction::RIGHT || dir == Direction::LEFT
    {
      if can_go(&Direction::UP, x, y, visited)
        && can_go(&Direction::DOWN, x, y, visited)
      {
        return;
      }
    }
  }

  visited[y][x] = true;
  let c: char = seq[idx];

  if c == 'D' || c == '?'
  {
    if can_go(&Direction::DOWN, x, y, visited)
    {
      search(x, y + 1, idx + 1, seq, Direction::DOWN, cnt, visited);
    }
  }

  if c == 'U' || c == '?'
  {
    if can_go(&Direction::UP, x, y, visited)
    {
      search(x, y - 1, idx + 1, seq, Direction::UP, cnt, visited);
    }
  }

  if c == 'R' || c == '?'
  {
    if can_go(&Direction::RIGHT, x, y, visited)
    {
      search(x + 1, y, idx + 1, seq, Direction::RIGHT, cnt, visited);
    }
  }

  if c == 'L' || c == '?'
  {
    if can_go(&Direction::LEFT, x, y, visited)
    {
      search(x - 1, y, idx + 1, seq, Direction::LEFT, cnt, visited);
    }
  }

  visited[y][x] = false;
}

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

  let pattern: String = scanner.next();

  let mut seq: Vec<char> = pattern.chars().collect();
  let mut cnt: u32 = 0;
  let mut visited: [[bool; N + 1]; N + 1] = [[false; N + 1]; N + 1];
  search(1, 1, 0, &mut seq, Direction::NONE, &mut cnt, &mut visited);

  print!(cnt, "\n");
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

fn main()
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
}
