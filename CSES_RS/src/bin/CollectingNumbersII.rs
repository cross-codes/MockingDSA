use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

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

  let n: usize = scanner.next();
  let m: usize = scanner.next();
  let mut x: [usize; 200001] = [0; 200001];
  let mut nums: [usize; 200001] = [0; 200001];

  for i in 1..n + 1
  {
    let val: usize = scanner.next();
    x[i] = val;
    nums[val] = i;
  }

  let mut result: usize = 1;
  for i in 1..n
  {
    if nums[i] > nums[i + 1]
    {
      result += 1;
    }
  }

  for _ in 0..m
  {
    let idx1: usize = scanner.next();
    let idx2: usize = scanner.next();

    let a: usize = x[idx1];
    let b: usize = x[idx2];

    if a > 1 && nums[a] < nums[a - 1]
    {
      result -= 1;
    }

    if a < n && nums[a + 1] < nums[a]
    {
      result -= 1;
    }

    if b > 1 && b - 1 != a && nums[b] < nums[b - 1]
    {
      result -= 1;
    }

    if b < n && b + 1 != a && nums[b + 1] < nums[b]
    {
      result -= 1;
    }

    x.swap(idx2, idx1);
    nums.swap(b, a);

    if a > 1 && nums[a] < nums[a - 1]
    {
      result += 1;
    }

    if a < n && nums[a + 1] < nums[a]
    {
      result += 1;
    }

    if b > 1 && b - 1 != a && nums[b] < nums[b - 1]
    {
      result += 1;
    }

    if b < n && b + 1 != a && nums[b + 1] < nums[b]
    {
      result += 1;
    }

    print!(result, "\n");
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
