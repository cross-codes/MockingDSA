use std::error::Error;
use std::io::{self, BufRead, BufWriter, Write};
use std::mem::swap;
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

  let n: i32 = scanner.next();
  let mut a: i32 = scanner.next();
  let mut b: i32 = scanner.next();

  let mut swapped: bool = false;
  if a > b
  {
    swap(&mut a, &mut b);
    swapped = true;
  }

  if a + b > n
  {
    display!("NO\n");
    return;
  }

  let x: i32 = n - (a + b);
  let mut player_one: Vec<i32> = vec![0; n as usize];
  let mut player_two: Vec<i32> = vec![0; n as usize];
  let mut counter: usize = 0;

  let mut l1: i32 = 1;
  let mut r1: i32 = n;
  let mut l2: i32 = 1;

  let mut a_cnt: i32 = 0;
  loop
  {
    if a_cnt == a
    {
      break;
    }

    player_one[counter] = r1;
    player_two[counter] = l2;
    r1 -= 1;
    l2 += 1;
    counter += 1;
    a_cnt += 1;
  }

  let l2_bef: i32 = l2;

  let mut x_cnt: i32 = 0;
  loop
  {
    if x_cnt == x
    {
      break;
    }

    player_one[counter] = l2;
    player_two[counter] = l2;
    l2 += 1;
    counter += 1;
    x_cnt += 1;
  }

  let l2_aft: i32 = l2;

  let mut b_cnt: i32 = 0;
  let mut once: bool = false;
  loop
  {
    if b_cnt == b
    {
      break;
    }

    if l1 < l2_bef
    {
      player_one[counter] = l1;
      player_two[counter] = l2;
      l2 += 1;
      l1 += 1;
    }
    else
    {
      if !once
      {
        l1 = l2_aft;
        once = true;
      }

      player_one[counter] = l1;
      player_two[counter] = l2;
      l2 += 1;
      l1 += 1;
    }

    counter += 1;
    b_cnt += 1;
  }

  let mut a_score: i32 = 0;
  let mut b_score: i32 = 0;
  for i in 0..n as usize
  {
    if player_one[i] > player_two[i]
    {
      a_score += 1;
    }
    else if player_one[i] < player_two[i]
    {
      b_score += 1;
    }
  }

  if a_score != a || b_score != b
  {
    display!("NO\n");
    return;
  }

  display!("YES\n");
  if !swapped
  {
    player_one.iter().for_each(|mov| {
      display!(mov, " ");
    });

    display!("\n");

    player_two.iter().for_each(|mov| {
      display!(mov, " ");
    });
  }
  else
  {
    player_two.iter().for_each(|mov| {
      display!(mov, " ");
    });

    display!("\n");

    player_one.iter().for_each(|mov| {
      display!(mov, " ");
    });
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
      let mut t: i32 = 1;
      t = scanner.next();

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
