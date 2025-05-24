pub struct IdempotentSparseTable<T>
where
  T: Copy,
{
  f: Box<dyn Fn(&T, &T) -> T>,
  table: Vec<Vec<T>>,
}

impl<T> IdempotentSparseTable<T>
where
  T: Copy,
{
  pub fn new(f: impl Fn(&T, &T) -> T + 'static, array: Vec<T>, n: usize)
    -> Self
  {
    let k: usize = n.ilog2() as usize;
    let mut table: Vec<Vec<T>> = vec![vec![array[0].clone(); n]; k + 1];
    table[0].copy_from_slice(&array);

    for y in 1..=k
    {
      let mut i: usize = 1 << (y - 1);
      for x in 0..=(n - (1 << y))
      {
        table[y][x] = f(&table[y - 1][x], &table[y - 1][i]);
        i += 1;
      }
    }

    Self {
      f: Box::new(f),
      table,
    }
  }

  pub fn query_range(&self, l: usize, r: usize) -> T
  {
    let i: usize = (r - l).ilog2() as usize;
    (self.f)(&self.table[i][l], &self.table[i][r - (1 << i)])
  }
}
