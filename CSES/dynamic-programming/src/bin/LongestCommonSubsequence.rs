use std::cmp::max;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

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

  let n: usize = scanner.next();
  let m: usize = scanner.next();
  let mut a: Vec<i32> = Vec::with_capacity(n + 1);
  a.push(-1);
  a.extend((0..n).map(|_| scanner.next::<i32>()));

  let mut b: Vec<i32> = Vec::with_capacity(m + 1);
  b.push(-1);
  b.extend((0..m).map(|_| scanner.next::<i32>()));
  let mut d: Vec<Vec<i32>> = vec![vec![0; m + 1]; n + 1];

  for y in 1..=n
  {
    for x in 1..=m
    {
      if a[y] == b[x]
      {
        d[y][x] = 1 + d[y - 1][x - 1];
      }
      else
      {
        d[y][x] = max(d[y - 1][x], d[y][x - 1]);
      }
    }
  }

  let mut c: Vec<i32> = Vec::new();
  let mut y: usize = n;
  let mut x: usize = m;

  while y != 0 || x != 0
  {
    if a[y] == b[x]
    {
      c.push(a[y]);
      y -= 1;
      x -= 1;
    }
    else
    {
      let mut left: i32 = -1;
      let mut up: i32 = -1;
      if y > 0
      {
        up = d[y - 1][x];
      }
      if x > 0
      {
        left = d[y][x - 1];
      }

      if up > left
      {
        y -= 1;
      }
      else
      {
        x -= 1;
      }
    }
  }

  display!(d[n][m], "\n");

  c.iter().rev().for_each(|c| {
    display!(c, " ");
  });

  display!("\n");
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
