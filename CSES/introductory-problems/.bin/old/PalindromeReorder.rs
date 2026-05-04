use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};

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

  let str: String = scanner.next();
  let chars: Vec<char> = str.chars().collect();
  let n: usize = chars.len();
  let mut freq: [i32; 26] = [0; 26];

  for ch in chars.iter()
  {
    let index = (*ch as u8 - b'A') as usize;
    freq[index] += 1;
  }

  let mut odd_letter: char = '$';
  let mut odd_index: usize = 0;
  for i in 0..26
  {
    if freq[i] & 1 != 0
    {
      if odd_letter != '$'
      {
        display!("NO SOLUTION\n");
        return;
      }
      else
      {
        odd_letter = (b'A' + (i as u8)) as char;
        odd_index = i;
      }
    }
  }

  let mut res: Vec<char> = vec!['$'; n];
  let mut left: usize = 0;
  let mut right: usize = n - 1;

  if odd_letter != '$'
  {
    for i in 0..26
    {
      if i == odd_index
      {
        continue;
      }

      let letter: char = (b'A' + (i as u8)) as char;
      let amt: i32 = freq[i];
      let mut left_dist: i32 = amt >> 1;
      let mut right_dist: i32 = left_dist;

      while left_dist > 0
      {
        res[left] = letter;
        left += 1;
        left_dist -= 1;
      }

      while right_dist > 0
      {
        res[right] = letter;
        right -= 1;
        right_dist -= 1;
      }
    }

    while left != right + 1
    {
      res[left] = odd_letter;
      left += 1;
    }
  }
  else
  {
    for i in 0..26
    {
      let letter: char = (b'A' + (i as u8)) as char;
      let amt: i32 = freq[i];
      let mut left_dist: i32 = amt >> 1;
      let mut right_dist: i32 = left_dist;

      while left_dist > 0
      {
        res[left] = letter;
        left += 1;
        left_dist -= 1;
      }

      while right_dist > 0
      {
        res[right] = letter;
        right -= 1;
        right_dist -= 1;
      }
    }
  }

  for i in 0..n
  {
    display!(res[i]);
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

  Ok(())
}
