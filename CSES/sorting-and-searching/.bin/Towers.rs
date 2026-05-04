use io::{ConsoleIO, IO};
use std::collections::{btree_map, BTreeMap};
use std::error::Error;
use std::ops::RangeBounds;

pub struct BTreeMultiset<T: Ord> {
  map: BTreeMap<T, usize>,
  size: usize,
}

pub struct Range<'a, T: 'a> {
  map_range: btree_map::Range<'a, T, usize>,
  cur_val: Option<&'a T>,
  cur_cnt: usize,
  cur_val_b: Option<&'a T>,
  cur_cnt_b: usize,
}

fn run(io: &mut impl IO, _case: u32) {
  let _: i32 = io.read();

  let mut towers: BTreeMultiset<i32> = BTreeMultiset::new();
  for k in io.read_iter::<i32>() {
    if let Some(key) = towers.range(k + 1..).next() {
      towers.remove_one(&key.clone());
    }

    towers.insert(k);
  }

  writeln!(io, "{}", towers.len()).unwrap()
}

fn main() -> Result<(), Box<dyn Error>> {
  let mut io = ConsoleIO::new();

  let t: u32 = 1;
  (1..=t).for_each(|i| run(&mut io, i));

  Ok(())
}

impl<'a, T: Ord> Iterator for Range<'a, T> {
  type Item = &'a T;

  fn next(&mut self) -> Option<Self::Item> {
    if self.cur_cnt > 0 {
      self.cur_cnt -= 1;
      return self.cur_val;
    }

    if let Some((val, &cnt)) = self.map_range.next() {
      self.cur_val = Some(val);
      self.cur_cnt = cnt - 1;
      return self.cur_val;
    }

    None
  }
}

impl<'a, T: Ord> DoubleEndedIterator for Range<'a, T> {
  fn next_back(&mut self) -> Option<Self::Item> {
    if self.cur_cnt_b > 0 {
      self.cur_cnt_b -= 1;
      return self.cur_val_b;
    }

    if let Some((val, &cnt)) = self.map_range.next_back() {
      self.cur_val_b = Some(val);
      self.cur_cnt_b = cnt - 1;
      return self.cur_val_b;
    }

    None
  }
}

impl<T: Ord> BTreeMultiset<T> {
  pub fn new() -> Self {
    BTreeMultiset {
      map: BTreeMap::new(),
      size: 0,
    }
  }

  pub fn insert(&mut self, value: T) -> bool {
    let cnt = self.map.entry(value).or_insert(0);
    *cnt += 1;
    self.size += 1;

    true
  }

  pub fn remove_one(&mut self, value: &T) -> bool {
    if let Some(cnt) = self.map.get_mut(value) {
      *cnt -= 1;
      if *cnt == 0 {
        self.map.remove(value);
      }

      self.size -= 1;
      return true;
    }

    false
  }

  pub fn remove_all(&mut self, value: &T) -> bool {
    if let Some(cnt) = self.map.remove(value) {
      self.size -= cnt;
      return true;
    }

    false
  }

  pub fn len(&self) -> usize {
    self.size
  }

  pub fn contains(&self, value: &T) -> bool {
    self.map.contains_key(value)
  }

  pub fn is_empty(&self) -> bool {
    self.size == 0
  }

  pub fn count(&self, value: &T) -> usize {
    self.map.get(value).cloned().unwrap_or(0)
  }

  pub fn range<R>(&self, range: R) -> Range<'_, T>
  where
    R: RangeBounds<T>,
  {
    Range {
      map_range: self.map.range(range),
      cur_val: None,
      cur_cnt: 0,
      cur_val_b: None,
      cur_cnt_b: 0,
    }
  }
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
