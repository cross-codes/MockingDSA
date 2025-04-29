use std::collections::HashSet;
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
  let _m: usize = scanner.next();
  let q: usize = scanner.next();

  let mut sets: Vec<HashSet<usize>> = vec![HashSet::new(); n + 1];
  let mut can_view_all: Vec<bool> = vec![false; n + 1];

  for _ in 0..q
  {
    let query_type: i32 = scanner.next();
    match query_type
    {
      1 =>
      {
        let x: usize = scanner.next();
        let y: usize = scanner.next();
        sets[x].insert(y);
      }

      2 =>
      {
        let x: usize = scanner.next();
        can_view_all[x] = true;
      }

      3 =>
      {
        let x: usize = scanner.next();
        let y: usize = scanner.next();

        if can_view_all[x] || sets[x].contains(&y)
        {
          print!("Yes\n");
        }
        else
        {
          print!("No\n");
        }
      }

      _ => unreachable!("Invalid query"),
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

fn main()
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
}
