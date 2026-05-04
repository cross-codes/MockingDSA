use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

fn two_sum(a: &[(i64, usize)], x: i64) -> Option<(usize, usize)>
{
  let mut l = 0;
  let mut r = a.len() - 1;

  while l < r
  {
    let sum = a[l].0 + a[r].0;
    if sum > x
    {
      r -= 1;
    }
    else if sum < x
    {
      l += 1;
    }
    else
    {
      return Some((a[l].1, a[r].1));
    }
  }
  None
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

  let n: usize = scanner.next();
  let x: i64 = scanner.next();
  let mut a: Vec<(i64, usize)> =
    (0..n).map(|i| (scanner.next(), i + 1)).collect();
  a.sort_unstable_by(|a, b| a.0.cmp(&b.0));

  for i in 0..n
  {
    for j in i + 1..n - 1
    {
      let target = x - (a[i].0 + a[j].0);
      if let Some((k, l)) = two_sum(&a[j + 1..], target)
      {
        display!(a[i].1, " ", a[j].1, " ", k, " ", l, "\n");
        return;
      }
    }
  }
  display!("IMPOSSIBLE\n");
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
