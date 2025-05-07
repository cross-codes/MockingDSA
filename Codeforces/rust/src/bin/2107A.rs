use std::cmp::max;
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
  let mut a: Vec<i32> = Vec::new();

  let mut all_same: bool = true;
  let mut max_element: i32 = scanner.next();
  let mut prev: i32 = max_element;
  a.push(max_element);

  for _ in 0..n - 1
  {
    let num: i32 = scanner.next();
    if all_same && prev != num
    {
      all_same = false;
    }

    a.push(num);
    prev = num;
    max_element = max(max_element, num);
  }

  if all_same
  {
    display!("No\n");
    return;
  }

  display!("Yes\n");

  let mut marked: bool = false;
  for i in 0..n
  {
    if !marked && a[i] == max_element
    {
      marked = true;
      display!("2 ");
    }
    else
    {
      display!("1 ");
    }
  }

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
  let stdin = io::stdin();
  let stdout = io::stdout();
  let mut scanner = Scanner::new(stdin.lock());
  let mut writer = BufWriter::new(stdout.lock());

  #[allow(unused_assignments)]
  let mut t: i32 = 1;
  t = scanner.next();

  for _ in 0..t
  {
    run(&mut scanner, &mut writer);
  }

  writer.flush().unwrap();

  Ok(())
}
