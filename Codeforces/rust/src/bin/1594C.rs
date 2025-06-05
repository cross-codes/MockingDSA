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
  let c: char = scanner.next();
  let s: Vec<char> = scanner.next::<String>().chars().collect();
  if s[n - 1] == c
  {
    for ch in s
    {
      if ch != c
      {
        display!("1\n");
        display!(n, "\n");
        return;
      }
    }

    display!("0\n");
  }
  else
  {
    for i in 1..=n
    {
      if n % i != 0
      {
        let mut possible = true;
        for j in (i..=(n / i) * i).step_by(i)
        {
          if s[j - 1] != c
          {
            possible = false;
            break;
          }
        }

        if possible
        {
          display!("1\n", i, "\n");
          return;
        }
      }
    }

    for i in 0..n - 1
    {
      if s[i] != c
      {
        display!("2\n", n, " ");
        for i in 1..=n
        {
          if n % i != 0
          {
            display!(i, "\n");
            return;
          }
        }
      }
    }

    // only back is unequal
    display!("1\n");
    for i in 1..=n
    {
      if n % i != 0
      {
        display!(i, "\n");
      }
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
      let mut t: i32 = 1;
      t = scanner.next();

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
