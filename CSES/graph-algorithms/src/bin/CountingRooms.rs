use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

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
  let m: usize = scanner.next();
  let grid: Vec<Vec<char>> = (0..n)
    .map(|_| scanner.next::<String>().chars().collect())
    .collect();

  let mut maze: Maze = Maze::new(&grid);

  let mut connected_components: i32 = 0;
  for y in 0..n
  {
    for x in 0..m
    {
      if maze.visited[y][x] == false && grid[y][x] == '.'
      {
        connected_components += 1;
        maze.dfs_visit(y as i32, x as i32);
      }
    }
  }


  display!(connected_components, "\n");
}

struct Maze<'a>
{
  pub dx: [i32; 4],
  pub dy: [i32; 4],
  pub grid: &'a Vec<Vec<char>>,
  pub visited: Vec<Vec<bool>>,

  num_rows: usize,
  num_cols: usize,
}

impl<'a> Maze<'a>
{
  pub fn new(grid: &'a Vec<Vec<char>>) -> Self
  {
    let num_rows: usize = grid.len();
    let num_cols: usize = grid[0].len();

    let dx: [i32; 4] = [1, 0, -1, 0];
    let dy: [i32; 4] = [0, 1, 0, -1];

    let visited: Vec<Vec<bool>> = vec![vec![false; num_cols]; num_rows];

    Maze {
      dx,
      dy,
      grid,
      visited,
      num_rows,
      num_cols,
    }
  }

  pub fn dfs_visit(&mut self, y: i32, x: i32)
  {
    if y >= self.num_rows as i32
      || y < 0
      || x >= self.num_cols as i32
      || x < 0
      || self.grid[y as usize][x as usize] == '#'
      || self.visited[y as usize][x as usize] == true
    {
      return;
    }

    self.visited[y as usize][x as usize] = true;
    for i in 0..4
    {
      self.dfs_visit(y + self.dy[i], x + self.dx[i]);
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
