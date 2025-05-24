use std::cmp::Reverse;
use std::collections::BinaryHeap;
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

  let x: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  let mut generator: MedianFinder = MedianFinder::new(x, k);

  for _ in 0..=n - k
  {
    display!(generator.next_median(), " ");
  }

  display!("\n");
}

pub struct MedianFinder
{
  stream: Vec<i32>,
  high: BinaryHeap<Reverse<i32>>,
  low: BinaryHeap<i32>,
  window_size: usize,
  pos: usize,
}

impl MedianFinder
{
  pub fn new(x: Vec<i32>, k: usize) -> Self
  {
    Self {
      stream: x,
      high: BinaryHeap::new(),
      low: BinaryHeap::new(),
      window_size: k,
      pos: 0,
    }
  }

  fn balance(&mut self) {}

  fn next_sequence(&mut self) {}

  pub fn next_median(&mut self) -> i32
  {
    self.next_sequence();

    if (self.high.len() + self.low.len()) & 1 != 0
    {
      return self.high.peek().cloned().unwrap().0;
    }
    else
    {
      return self.low.peek().cloned().unwrap();
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
