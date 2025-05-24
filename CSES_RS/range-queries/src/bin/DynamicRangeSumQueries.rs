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

  let x: Vec<i64> = (0..n).map(|_| scanner.next()).collect();
  let mut bit: BinaryIndexedTree = BinaryIndexedTree::new(&x, n);

  for _ in 0..q
  {
    let option: i8 = scanner.next();
    if option == 1
    {
      let k: isize = scanner.next();
      let u: i64 = scanner.next();
      bit.advance_value(k, u - bit.under_array[k as usize]);
      bit.under_array[k as usize] = u;
    }
    else
    {
      let (a, b): (isize, isize) = (scanner.next(), scanner.next());
      display!(bit.prefix_sum_at(b) - bit.prefix_sum_at(a - 1), "\n");
    }
  }
}

pub struct BinaryIndexedTree
{
  tree: Vec<i64>,
  pub under_array: Vec<i64>,
}

impl BinaryIndexedTree
{
  pub fn new(array: &Vec<i64>, n: usize) -> Self
  {
    let mut tree: Vec<i64> = vec![0; n + 1];
    let mut under_array: Vec<i64> = vec![0; n + 1];
    for i in 1..=n
    {
      let mut k: isize = i as isize;
      while k <= n as isize
      {
        tree[k as usize] += array[i - 1];
        k += k & -k;
      }
      under_array[i] = array[i - 1];
    }

    Self { tree, under_array }
  }

  pub fn prefix_sum_at(&self, mut k: isize) -> i64
  {
    let mut s: i64 = 0;
    while k >= 1
    {
      s += self.tree[k as usize];
      k -= k & -k;
    }

    s
  }

  pub fn advance_value(&mut self, mut k: isize, amt: i64)
  {
    while k <= self.tree.len() as isize
    {
      self.tree[k as usize] += amt;
      k += k & -k;
    }
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
