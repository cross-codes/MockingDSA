use std::collections::BTreeSet;
use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

fn permute<F>(vector: &mut Vec<char>, mut length: usize, procedure: &mut F)
where
  F: FnMut(&mut Vec<char>),
{
  if length == 1
  {
    procedure(vector);
  }
  else
  {
    length -= 1;
    permute(vector, length, procedure);

    for i in 0..length
    {
      let index = if length & 1 == 0 { 0 } else { i };
      vector.swap(index, length);
      permute(vector, length, procedure);
    }
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

  let mut a: Vec<char> = scanner.next::<String>().chars().collect();
  let n: usize = a.len();

  let mut set: BTreeSet<Vec<char>> = BTreeSet::new();

  permute(&mut a, n, &mut |vector| {
    set.insert(vector.to_vec());
  });

  display!(set.len(), "\n");

  for v in set
  {
    v.iter().for_each(|c| {
      display!(c);
    });

    display!("\n");
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
