use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

type PreComp = Vec<i64>;

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
  data: &mut PreComp,
) {
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
  for k in 1..n + 1 {
    display!(data[k - 1], "\n");
  }
}

struct Scanner<B> {
  reader: B,
  buffer: Vec<String>,
  pos: usize,
}

impl<B: BufRead> Scanner<B> {
  fn new(reader: B) -> Self {
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

  fn ensure_buffered(&mut self) {
    if self.pos >= self.buffer.len() {
      let mut line = String::new();
      self.reader.read_line(&mut line).unwrap();
      self.buffer = line.split_whitespace().map(|s| s.to_owned()).collect();
      self.pos = 0;
    }
  }
}

fn main() -> Result<(), Box<dyn Error>> {
  let stdin = io::stdin();
  let stdout = io::stdout();
  let mut scanner = Scanner::new(stdin.lock());
  let mut writer = BufWriter::new(stdout.lock());

  #[allow(unused_assignments)]
  let t: i32 = 1;

  let mut results: Vec<i64> = (1..10001)
    .map(|n| {
      let n = n as i64;
      ((n * n * ((n * n) - 1)) >> 1) - (((n - 1) * (n - 2)) << 2)
    })
    .collect();

  for _ in 0..t {
    run(&mut scanner, &mut writer, &mut results);
  }

  writer.flush().unwrap();

  Ok(())
}
