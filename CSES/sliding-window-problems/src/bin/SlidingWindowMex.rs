use std::collections::{BTreeSet, HashMap};
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
  let k: usize = scanner.next();

  let mut set: BTreeSet<i32> = (0..=200000).collect();
  let mut freq: HashMap<i32, usize> = HashMap::new();
  let x: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  for i in 0..k
  {
    let num: i32 = x[i];
    let mut prev_freq: usize = 0;

    if freq.contains_key(&num)
    {
      prev_freq = freq[&num];
    }

    freq.insert(num, prev_freq + 1);
    set.remove(&num);
  }

  display!(set.iter().next().unwrap(), " ");

  let mut window_start: usize = 0;

  for i in k..n
  {
    let prev_num: i32 = x[window_start];
    let prev_freq: usize = freq[&prev_num];
    if prev_freq == 1
    {
      freq.remove(&prev_num);
      set.insert(prev_num);
    }
    else
    {
      freq.insert(prev_num, prev_freq - 1);
    }

    window_start += 1;

    let curr_num: i32 = x[i];
    let mut curr_freq: usize = 0;
    if freq.contains_key(&curr_num)
    {
      curr_freq = freq[&curr_num];
    }

    freq.insert(curr_num, curr_freq + 1);
    set.remove(&curr_num);

    display!(set.iter().next().unwrap(), " ");
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
