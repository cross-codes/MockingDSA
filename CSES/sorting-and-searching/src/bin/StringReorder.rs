use std::collections::BTreeMap;
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

  let string: Vec<char> = scanner.next::<String>().chars().collect();
  let n: usize = string.len();
  let mut map: BTreeMap<char, i32> =
    string.into_iter().fold(BTreeMap::new(), |mut acc, ch| {
      *acc.entry(ch).or_insert(0) += 1;
      acc
    });

  let mut result: Vec<char> = vec!['$'; n];
  let mut ptr: usize = n - 1;

  match map.iter().last()
  {
    Some((&key, &(mut value))) =>
    {
      while value > 0
      {
        result[ptr] = key;
        ptr -= 2;
        value -= 1;
      }

      map.remove(&key);
    }
    _ => (),
  }

  result.iter().for_each(|c| {
    display!(c);
  });

  display!("\n");

  ptr = 0;
  while ptr != n
  {
    let curr: char = result[ptr];
    if curr != '$'
    {
      ptr += 1;
      continue;
    }

    let next_entry = map.iter().skip_while(|&(key, _)| *key == curr).next();

    match next_entry
    {
      Some((&key, &value)) =>
      {
        ptr += 1;
        result[ptr] = key;

        if value > 1
        {
          map.insert(key, value - 1);
        }
        else
        {
          map.remove(&key);
        }
      }
      _ =>
      {
        display!("-1\n");
        return;
      }
    }
  }

  result.iter().for_each(|c| {
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
