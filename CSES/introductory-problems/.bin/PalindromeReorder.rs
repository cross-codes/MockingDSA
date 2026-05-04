use io::{ConsoleIO, IO};
use std::collections::HashMap;
use std::error::Error;

fn run(io: &mut impl IO, _case: u32) {
  let line = io.read_line();
  let mut freq: HashMap<char, usize> = HashMap::new();
  let mut len: usize = 0;

  for c in line.chars() {
    let amt = freq.entry(c).or_insert(0);
    *amt += 1;
    len += 1;
  }

  let mut n_odd = 0;
  freq
    .iter()
    .for_each(|(_, v)| n_odd += if v & 1 != 0 { 1 } else { 0 });

  if len & 1 != 0 {
    let mut res: Vec<char> = vec!['?'; len];
    if n_odd != 1 {
      writeln!(io, "NO SOLUTION").unwrap()
    } else {
      let mut char_odd = '?';
      let (mut l, mut r) = (0, len - 1);
      freq.iter_mut().for_each(|(k, v)| {
        if *v & 1 != 0 {
          res[len >> 1] = *k;
          char_odd = *k;
        } else {
          while *v != 0 {
            res[l] = *k;
            res[r] = *k;
            l += 1;
            r -= 1;
            *v -= 2;
          }
        }
      });

      res.iter_mut().for_each(|c| {
        if *c == '?' {
          *c = char_odd;
        }
      });

      writeln!(io, "{}", String::from_iter(res.iter())).unwrap();
    }
  } else {
    let mut res: Vec<char> = vec!['?'; len];
    if n_odd != 0 {
      writeln!(io, "NO SOLUTION").unwrap()
    } else {
      let (mut l, mut r) = (0, len - 1);
      freq.iter_mut().for_each(|(k, v)| {
        if *v & 1 != 0 {
          res[len >> 1] = *k;
        } else {
          while *v != 0 {
            res[l] = *k;
            res[r] = *k;
            l += 1;
            r -= 1;
            *v -= 2;
          }
        }
      });
      writeln!(io, "{}", String::from_iter(res.iter())).unwrap();
    }
  }
}

fn main() -> Result<(), Box<dyn Error>> {
  let mut io = ConsoleIO::new();

  let t: u32 = 1;
  (1..=t).for_each(|i| run(&mut io, i));

  Ok(())
}

pub mod io {
  use std::{
    fmt::{self, Debug},
    io::{BufRead, BufReader, Stdin},
    str::FromStr,
  };

  pub trait IO: fmt::Write {
    fn read_line(&mut self) -> &str;

    fn read<F: FromStr>(&mut self) -> F
    where
      F::Err: Debug,
    {
      self.read_line().parse().unwrap()
    }

    fn read_iter<'a, T: FromStr>(&'a mut self) -> Iter<'a, T>
    where
      T::Err: Debug,
    {
      Iter {
        iter: self.read_line().split_whitespace(),
        _marker: std::marker::PhantomData,
      }
    }

    fn read_array<T: FromStr, const N: usize>(&mut self) -> [T; N]
    where
      T::Err: Debug,
    {
      let mut iter = self.read_iter();
      [(); N].map(|()| iter.next().unwrap())
    }

    fn write(&mut self, s: &str);
  }

  pub struct Iter<'a, T> {
    iter: std::str::SplitWhitespace<'a>,
    _marker: std::marker::PhantomData<T>,
  }

  impl<'a, T: FromStr> Iterator for Iter<'a, T>
  where
    T::Err: Debug,
  {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
      let next = self.iter.next()?;
      Some(next.parse().unwrap())
    }
  }

  pub struct ConsoleIO {
    reader: BufReader<Stdin>,
    input: String,
    output: String,
  }

  impl ConsoleIO {
    pub fn new() -> Self {
      Self {
        reader: BufReader::new(std::io::stdin()),
        input: String::new(),
        output: String::with_capacity(2_000_000),
      }
    }
  }

  impl IO for ConsoleIO {
    fn read_line(&mut self) -> &str {
      self.input = String::new();
      self.reader.read_line(&mut self.input).unwrap();
      self.input.trim_end()
    }

    fn write(&mut self, s: &str) {
      self.output.push_str(s);
    }
  }

  impl fmt::Write for ConsoleIO {
    fn write_str(&mut self, s: &str) -> fmt::Result {
      write!(&mut self.output, "{s}")
    }
  }

  impl Drop for ConsoleIO {
    fn drop(&mut self) {
      println!("{}", self.output);
    }
  }

  pub struct DebugIO<'a> {
    input: std::str::Lines<'a>,
    line: &'a str,
    pub output: String,
  }

  impl<'a> DebugIO<'a> {
    pub fn new(input: &'a str) -> Self {
      Self {
        input: input.lines(),
        line: "",
        output: String::new(),
      }
    }

    pub fn output(&self) -> &str {
      self.output.trim_end()
    }
  }

  impl IO for DebugIO<'_> {
    fn read_line(&mut self) -> &str {
      self.line = self.input.next().unwrap();
      self.line.trim_end()
    }

    fn write(&mut self, s: &str) {
      self.output.push_str(s);
    }
  }

  impl fmt::Write for DebugIO<'_> {
    fn write_str(&mut self, s: &str) -> fmt::Result {
      write!(&mut self.output, "{s}")
    }
  }
}
