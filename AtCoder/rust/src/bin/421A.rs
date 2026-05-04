use std::io;

fn main() {
  let mut n = String::new();

  io::stdin().read_line(&mut n).unwrap();
  let n: usize = n.trim().parse().unwrap();
  let mut s: Vec<String> = Vec::with_capacity(n);

  for _ in 0..n {
    let mut name = String::new();
    io::stdin().read_line(&mut name).unwrap();
    s.push(name.trim().to_string());
  }

  let mut line = String::new();
  io::stdin().read_line(&mut line).unwrap();

  let mut parts = line.trim().split_whitespace();
  let x: usize = parts.next().unwrap().parse().unwrap();
  let y: String = parts.next().unwrap().to_string();

  if s[x - 1] == y {
    println!("Yes");
  } else {
    println!("No");
  }
}
