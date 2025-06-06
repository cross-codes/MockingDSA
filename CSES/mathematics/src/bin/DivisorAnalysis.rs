use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::thread::{self, JoinHandle};

fn mod_pow(x: i32, n: i64, m: i64) -> i32
{
  let mut res: i64 = 1;
  let mut i: i64 = 1;
  let mut j: i64 = x as i64;
  while i <= n
  {
    if i & n != 0
    {
      res = res * j % m;
    }

    j = j * j % m;
    i <<= 1;
  }

  res as i32
}

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

  let modulus: i64 = 1000000007;
  let n: usize = scanner.next();
  let mut prime: Vec<i32> = Vec::new();
  let mut power: Vec<i32> = Vec::new();

  for _ in 0..n
  {
    let p: i32 = scanner.next();
    let alpha: i32 = scanner.next();
    prime.push(p);
    power.push(alpha);
  }

  let mut num_factors: i32 = 1;
  let mut sum_factors: i32 = 1;
  for i in 0..n
  {
    num_factors =
      ((num_factors as i64 * (power[i] + 1) as i64) % modulus) as i32;

    let numerator: i128 =
      mod_pow(prime[i], (power[i] + 1) as i64, modulus) as i128 - 1;
    let denominator: i128 = mod_pow(prime[i] - 1, modulus - 2, modulus) as i128;

    sum_factors = ((sum_factors as i128 * numerator * denominator)
      % modulus as i128) as i32;
  }

  display!(num_factors, " ", sum_factors, " ");

  let mut divide_necessary: bool = true;
  let mut exponent: i32 = 1;
  for i in 0..n
  {
    let mut temp = exponent as i64 * (power[i] + 1) as i64;
    if divide_necessary && (power[i] + 1) % 2 == 0
    {
      temp /= 2;
      divide_necessary = false;
    }

    exponent = (temp % (modulus - 1)) as i32;
  }

  let mut product_factors: i32 = 1;
  for i in 0..n
  {
    if divide_necessary
    {
      product_factors = ((product_factors as i64
        * mod_pow(prime[i], (power[i] >> 1) as i64 * exponent as i64, modulus)
          as i64)
        % modulus) as i32;
    }
    else
    {
      product_factors = ((product_factors as i64
        * mod_pow(prime[i], power[i] as i64 * exponent as i64, modulus) as i64)
        % modulus) as i32;
    }
  }

  display!(product_factors, "\n");
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
