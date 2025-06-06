use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

fn mod_pow(x: i32, n: i32, m: i64) -> i32
{
  if n == 0
  {
    return 1 % m as i32;
  }

  let mut u: i64 = mod_pow(x, n >> 1, m) as i64;
  u = (u * u) % m;

  if n & 1 != 0
  {
    u = (u * x as i64) % m;
  }

  return u as i32;
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

  let a: i32 = scanner.next();
  let b: i32 = scanner.next();
  let c: i32 = scanner.next();
  let modulus: i64 = 1000000007;

  let k: i32 = mod_pow(b, c, modulus - 1);
  display!(mod_pow(a, k, modulus), "\n");
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
      let mut n: i32 = 1;
      n = scanner.next();

      (1..=n).for_each(|i| run(&mut scanner, &mut writer, i));
      writer.flush().unwrap();
    })
    .expect(&format!(
      "Failed to spawn thread. [STACK SIZE {} bytes]",
      stack_size
    ));

  handle.join().unwrap();
  Ok(())
}
