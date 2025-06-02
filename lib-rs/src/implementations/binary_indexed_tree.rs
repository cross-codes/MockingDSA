pub struct BinaryIndexedTree
{
  tree: Vec<i64>,
  pub under_array: Vec<i64>,
}

impl BinaryIndexedTree
{
  pub fn new(array: Vec<i64>, n: usize) -> Self
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
