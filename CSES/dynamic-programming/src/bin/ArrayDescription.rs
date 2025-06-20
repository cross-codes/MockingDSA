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

  const MOD: i64 = 1000000007;
  let n: usize = scanner.next();
  let m: usize = scanner.next();
  let x: Vec<usize> = (0..n).map(|_| scanner.next()).collect();

  let mut arrays: Vec<Vec<i64>> = vec![vec![0; m + 1]; n];
  if x[0] == 0
  {
    for i in 1..=m
    {
      arrays[0][i] = 1;
    }
  }
  else
  {
    arrays[0][x[0]] = 1;
  }

  for i in 1..n
  {
    if x[i] != 0
    {
      arrays[i][x[i]] = arrays[i - 1][x[i]];

      if x[i] > 1
      {
        arrays[i][x[i]] += arrays[i - 1][x[i] - 1];
      }

      if x[i] < m
      {
        arrays[i][x[i]] += arrays[i - 1][x[i] + 1];
      }

      arrays[i][x[i]] %= MOD;
    }
    else
    {
      for j in 1..=m
      {
        arrays[i][j] += arrays[i - 1][j];

        if j != 1
        {
          arrays[i][j] += arrays[i - 1][j - 1];
        }
        if j != m
        {
          arrays[i][j] += arrays[i - 1][j + 1];
        }

        arrays[i][j] %= MOD;
      }
    }
  }

  let mut res: i64 = 0;
  for i in 1..=m
  {
    res += arrays[n - 1][i];
    res %= MOD;
  }

  display!(res, "\n");
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
