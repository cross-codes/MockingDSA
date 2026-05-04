use std::collections::HashMap;
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

  let mut map: HashMap<i32, i32> = HashMap::new();
  let x: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  for i in 0..k
  {
    if map.contains_key(&x[i])
    {
      let freq: i32 = map[&x[i]];
      map.insert(x[i], freq + 1);
    }
    else
    {
      map.insert(x[i], 1);
    }
  }

  display!(map.len(), " ");

  let mut window_start: usize = 0;
  for i in k..n
  {
    let to_remove: i32 = x[window_start];
    if map[&to_remove] == 1
    {
      map.remove(&to_remove);
    }
    else
    {
      let freq: i32 = map[&to_remove];
      map.insert(to_remove, freq - 1);
    }

    if map.contains_key(&x[i])
    {
      let freq: i32 = map[&x[i]];
      map.insert(x[i], freq + 1);
    }
    else
    {
      map.insert(x[i], 1);
    }

    display!(map.len(), " ");
    window_start += 1;
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
