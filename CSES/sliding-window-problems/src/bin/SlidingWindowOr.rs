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

  let (x0, a, b, c): (u32, u32, u32, u32) = (
    scanner.next(),
    scanner.next(),
    scanner.next(),
    scanner.next(),
  );

  let mut result: u32 = 0;

  let mut or_value: u32 = x0;
  let mut freq: [u32; 32] = [0; 32];
  (0..32).for_each(|pos: usize| {
    if ((or_value >> pos) & 1) > 0
    {
      freq[pos] += 1;
    }
  });

  let mut x: Vec<u32> = vec![0; n];
  x[0] = x0;
  for i in 1..k
  {
    x[i] = ((a as u64 * x[i - 1] as u64 + b as u64) % c as u64) as u32;
    or_value |= x[i];

    let mut curr: u32 = x[i];
    while curr > 0
    {
      let pos: usize = curr.trailing_zeros() as usize;
      freq[pos] += 1;
      curr &= curr - 1;
    }
  }

  result ^= or_value;

  let mut window_start: usize = 0;
  for i in k..n
  {
    x[i] = ((a as u64 * x[i - 1] as u64 + b as u64) % c as u64) as u32;

    let mut curr: u32 = x[i];
    while curr > 0
    {
      let pos: usize = curr.trailing_zeros() as usize;
      if freq[pos] == 0
      {
        or_value |= 1 << pos;
      }

      freq[pos] += 1;
      curr &= curr - 1;
    }

    curr = x[window_start];
    while curr > 0
    {
      let pos: usize = curr.trailing_zeros() as usize;
      if freq[pos] == 1
      {
        or_value ^= 1 << pos;
      }

      freq[pos] -= 1;
      curr &= curr - 1;
    }

    window_start += 1;
    result ^= or_value;
  }

  display!(result, "\n");
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
