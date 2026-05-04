use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

type Precalc = [i64; 1000001];
const MOD: i64 = 1000000007;

fn run(
  scanner: &mut Scanner<io::StdinLock>,
  writer: &mut BufWriter<io::StdoutLock>,
  _case: i32,
  ways_to_sum: &Precalc,
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
  display!(ways_to_sum[n], "\n");
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

      let mut ways_to_sum: Precalc = [0; 1000001];
      ways_to_sum[0] = 0;

      for i in 1..=1000000
      {
        for j in 1..=6
        {
          if i - j > 0
          {
            ways_to_sum[i] += ways_to_sum[i - j];
          }
          else if i - j == 0
          {
            ways_to_sum[i] += 1;
            break;
          }
        }
        ways_to_sum[i] %= MOD;
      }

      (1..=t).for_each(|i| run(&mut scanner, &mut writer, i, &ways_to_sum));
      writer.flush().unwrap();
    })
    .expect(&format!(
      "Failed to spawn thread [STACK SIZE {} B]",
      stack_size
    ));

  handle.join().unwrap();
  Ok(())
}
