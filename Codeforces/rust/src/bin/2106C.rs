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
  let k: i32 = scanner.next();

  let mut a: Vec<i32> = vec![0; n];
  let mut b: Vec<i32> = vec![0; n];

  for i in 0..n
  {
    a[i] = scanner.next();
  }

  for i in 0..n
  {
    b[i as usize] = scanner.next();
  }

  let mut unsolvable: bool = false;
  let mut target_sum: i32 = i32::MIN;
  let mut min_in_range: i32 = i32::MAX;
  let mut max_in_range: i32 = i32::MIN;
  for i in 0..n
  {
    if b[i] != -1
    {
      let value = a[i] + b[i];
      if target_sum != i32::MIN
      {
        if value != target_sum
        {
          unsolvable = true;
        }
      }
      else
      {
        target_sum = value;
      }
    }

    min_in_range = std::cmp::min(min_in_range, a[i]);
    max_in_range = std::cmp::max(max_in_range, a[i]);
  }

  if unsolvable
  {
    print!(0, "\n");
    return;
  }

  let res: i32;

  if target_sum == i32::MIN
  {
    if max_in_range - min_in_range > k
    {
      print!(0, "\n");
      return;
    }
    else
    {
      let lower_limit: i32 = max_in_range;
      let upper_limit: i32 = min_in_range + k;
      res = upper_limit - lower_limit + 1;
    }
  }
  else
  {
    if min_in_range + k < target_sum || max_in_range > target_sum
    {
      res = 0;
    }
    else
    {
      res = 1;
    }
  }

  print!(res, "\n");
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
