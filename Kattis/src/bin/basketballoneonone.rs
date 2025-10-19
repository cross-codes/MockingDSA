use std::io;

fn main() {
  let mut s = String::new();
  io::stdin().read_line(&mut s).unwrap();
  let s_t = s.trim().to_string();
  println!("{}", s_t.chars().nth(s_t.len() - 2).unwrap());
}
