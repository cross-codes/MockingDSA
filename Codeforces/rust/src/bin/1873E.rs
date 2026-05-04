use std::cmp;
use std::io::{self, BufRead, BufWriter, Write};

static mut ARRAY: [i64; 200001] = [0; 200001];

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
)
{
  #[allow(unused_macros)]
  macro_rules! print {
        () => {
            writeln!(writer).unwrap();
        };
        ($arg:expr) => {
            write!(writer, "{}\n", $arg).unwrap();
        };
        ($arg:expr, $($rest:expr),*) => {
            write!(writer, "{} ", $arg).unwrap();
            print!($($rest),*);
        };
    }

  let n: usize = scanner.next();
  let x: i64 = scanner.next();

  let mut min_height: i64 = i64::MAX;
  let mut max_height: i64 = i64::MIN;

  unsafe {
    for i in 0..n
    {
      let value = scanner.next();
      min_height = cmp::min(min_height, value);
      max_height = cmp::max(max_height, value);
      ARRAY[i as usize] = value;
    }

    let predicate = |m: i64| -> bool {
      let mut water: i64 = 0i64;
      for i in 0..n
      {
        water += cmp::max(m - ARRAY[i], 0i64);
      }

      water > x
    };

    let mut l = min_height - 1;
    let mut r = x + max_height + 1;

    while r - l > 1
    {
      let m = l + ((r - l) >> 1);
      if predicate(m)
      {
        r = m;
      }
      else
      {
        l = m;
      }
    }

    print!(l);
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

fn main()
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
}
