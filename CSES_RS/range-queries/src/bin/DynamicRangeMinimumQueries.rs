use std::cmp::min;
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
  let q: i32 = scanner.next();

  let x: Vec<i32> = (0..n).map(|_| scanner.next()).collect();

  let min_select: Box<dyn Fn(&i32, &i32) -> i32> = Box::new(|a, b| min(*a, *b));
  let mut segment_tree: SegmentTree<i32> =
    SegmentTree::new(&x, n, i32::MAX, min_select);

  for _ in 0..q
  {
    let option: i8 = scanner.next();
    if option == 1
    {
      let k: usize = scanner.next();
      let u: i32 = scanner.next();
      segment_tree.set_at_index(k - 1, u);
    }
    else
    {
      let (a, b): (usize, usize) = (scanner.next(), scanner.next());
      display!(segment_tree.query_range(a - 1, b), "\n");
    }
  }
}

pub struct SegmentTree<T>
where
  T: Copy,
{
  f: Box<dyn Fn(&T, &T) -> T>,
  tree: Vec<T>,
  offset: usize,
  default_value: T,
}

impl<T> SegmentTree<T>
where
  T: Copy,
{
  pub fn new(
    array: &Vec<T>,
    n: usize,
    default_value: T,
    f: impl Fn(&T, &T) -> T + 'static,
  ) -> Self
  {
    let ceil_log2 = if n == 1
    {
      1
    }
    else
    {
      64 - (n - 1).leading_zeros() as usize
    };

    let offset: usize = 1usize << ceil_log2;
    let mut tree: Vec<T> = vec![default_value; offset << 1];
    tree[offset..offset + n].copy_from_slice(&array);

    let mut i: usize = offset;
    while i != 1
    {
      let mut j: usize = i;
      while j < (i << 1)
      {
        tree[j >> 1] = f(&tree[j], &tree[j + 1]);
        j += 2;
      }
      i >>= 1;
    }

    Self {
      f: Box::new(f),
      tree,
      offset,
      default_value,
    }
  }

  pub fn set_at_index(&mut self, mut index: usize, value: T)
  {
    index += self.offset;
    self.tree[index] = value;

    while index != 1
    {
      self.tree[index >> 1] =
        (self.f)(&self.tree[index], &self.tree[index ^ 1]);

      index >>= 1;
    }
  }

  pub fn query_range(&self, mut l: usize, mut r: usize) -> T
  {
    l += self.offset;
    r += self.offset;

    let mut result = self.default_value;
    while l < r
    {
      if l & 1 != 0
      {
        result = (self.f)(&result, &self.tree[l]);
        l += 1;
      }
      if r & 1 != 0
      {
        r -= 1;
        result = (self.f)(&result, &self.tree[r]);
      }

      l >>= 1;
      r >>= 1;
    }

    result
  }
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
