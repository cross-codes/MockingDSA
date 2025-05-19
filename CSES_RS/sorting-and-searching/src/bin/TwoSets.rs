use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn gauss_add(
  incl_start: i32,
  incl_end: i32,
  set1: &mut Vec<i32>,
  set2: &mut Vec<i32>,
)
{
  let mid: i32 = incl_start + ((incl_end - incl_start) >> 1);
  let mut idx: i32 = incl_start;

  let mut add_to_first: bool = true;
  while idx <= mid
  {
    if add_to_first
    {
      set1.push(idx);
      set1.push(incl_end - idx + incl_start);
    }
    else
    {
      set2.push(idx);
      set2.push(incl_end - idx + incl_start);
    }

    idx += 1;
    add_to_first = !add_to_first;
  }
}

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

  let n: i32 = scanner.next();
  if n == 1 || n == 2
  {
    display!("NO\n");
  }
  else if n % 4 == 0
  {
    display!("YES\n");

    let mut set1: Vec<i32> = Vec::new();
    let mut set2: Vec<i32> = Vec::new();
    gauss_add(1, n, &mut set1, &mut set2);

    display!(set1.len(), "\n");
    set1.iter().for_each(|x| {
      display!(x, " ");
    });

    display!("\n");

    display!(set2.len(), "\n");
    set2.iter().for_each(|x| {
      display!(x, " ");
    });

    display!("\n");
  }
  else if (n - 3) % 4 == 0
  {
    display!("YES\n");

    let mut set1: Vec<i32> = vec![1, 2];
    let mut set2: Vec<i32> = vec![3];
    gauss_add(4, n, &mut set1, &mut set2);

    display!(set1.len(), "\n");
    set1.iter().for_each(|x| {
      display!(x, " ");
    });

    display!("\n");

    display!(set2.len(), "\n");
    set2.iter().for_each(|x| {
      display!(x, " ");
    });

    display!("\n");
  }
  else
  {
    display!("NO\n");
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

  (0..t).for_each(|_| run(&mut scanner, &mut writer));
  writer.flush().unwrap();

  Ok(())
}
