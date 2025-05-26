use std::cmp::min;
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
  let k: usize = scanner.next();

  let (x0, a, b, c): (i32, i32, i32, i32) = (
    scanner.next(),
    scanner.next(),
    scanner.next(),
    scanner.next(),
  );

  let mut x: Vec<i32> = vec![0; n];
  x[0] = x0;
  for i in 1..n
  {
    x[i] = ((a as i64 * (x[i - 1] as i64) + b as i64) % c as i64) as i32;
  }

  let min_select: Box<dyn Fn(&i32, &i32) -> i32> = Box::new(|a, b| min(*a, *b));
  let sparse_table: IdempotentSparseTable<i32> =
    IdempotentSparseTable::new(min_select, &x, n);

  let mut res: i32 = 0;
  for i in 0..=n - k
  {
    res ^= sparse_table.query_range(i, i + k);
  }

  display!(res, "\n");
}

pub struct IdempotentSparseTable<T>
where
  T: Copy,
{
  f: Box<dyn Fn(&T, &T) -> T>,
  table: Vec<Vec<T>>,
}

impl<T> IdempotentSparseTable<T>
where
  T: Copy,
{
  pub fn new(
    f: impl Fn(&T, &T) -> T + 'static,
    array: &Vec<T>,
    n: usize,
  ) -> Self
  {
    let k: usize = n.ilog2() as usize;
    let mut table: Vec<Vec<T>> = vec![vec![array[0]; n]; k + 1];
    table[0].copy_from_slice(&array);

    for y in 1..=k
    {
      let mut i: usize = 1 << (y - 1);
      for x in 0..=(n - (1 << y))
      {
        table[y][x] = f(&table[y - 1][x], &table[y - 1][i]);
        i += 1;
      }
    }

    Self {
      f: Box::new(f),
      table,
    }
  }

  pub fn query_range(&self, l: usize, r: usize) -> T
  {
    let i: usize = (r - l).ilog2() as usize;
    (self.f)(&self.table[i][l], &self.table[i][r - (1 << i)])
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
