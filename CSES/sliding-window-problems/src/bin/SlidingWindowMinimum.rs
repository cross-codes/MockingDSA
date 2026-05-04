use std::collections::VecDeque;
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
  let mut queue: VecDeque<i32> = VecDeque::new();

  for i in 1..n
  {
    x[i] = ((a as i64 * (x[i - 1] as i64) + b as i64) % c as i64) as i32;
  }

  for i in 0..k
  {
    while !queue.is_empty() && *queue.back().unwrap() > x[i]
    {
      queue.pop_back();
    }

    queue.push_back(x[i]);
  }

  let mut res: i32 = *queue.front().unwrap();
  let mut window_begin: usize = 0;
  for i in k..n
  {
    if *queue.front().unwrap() == x[window_begin]
    {
      queue.pop_front();
    }

    let next: i32 = x[i];
    window_begin += 1;

    while !queue.is_empty() && *queue.back().unwrap() > next
    {
      queue.pop_back();
    }

    queue.push_back(next);
    res ^= *queue.front().unwrap();
  }

  display!(res, "\n");
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
