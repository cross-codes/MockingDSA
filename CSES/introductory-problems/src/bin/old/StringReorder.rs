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

  let s: Vec<char> = scanner.next::<String>().chars().collect();
  let n: usize = s.len();

  let mut ans: Vec<char> = Vec::new();

  let mut freq: [usize; 26] = [0; 26];
  for c in s
  {
    freq[((c as u8) - ('A' as u8)) as usize] += 1;
  }

  let max_freq: usize = *freq.iter().max().unwrap();
  if max_freq > ((n + 1) >> 1)
  {
    display!("-1\n");
    return;
  }

  let mut prev: char = '$';
  for i in 0..n
  {
    let mut pick: i32 = -1;
    for c in 0..26
    {
      if freq[c] == 0 || (c as u8 + 'A' as u8) == prev as u8
      {
        continue;
      }
      freq[c] -= 1;
      let max_freq_left: usize = *freq.iter().max().unwrap();

      if max_freq_left <= ((n - i) >> 1)
      {
        pick = c as i32;
        break;
      }

      freq[c] += 1;
    }

    if pick == -1
    {
      display!("-1\n");
      return;
    }

    ans.push(('A' as u8 + pick as u8) as char);
    prev = ('A' as u8 + pick as u8) as char;
  }

  ans.iter().for_each(|c| {
    display!(c);
  });

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
