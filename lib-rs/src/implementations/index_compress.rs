pub struct IndexCompress<T>
where
  T: Ord + Clone,
{
  compressed_vals: Vec<T>,
}

impl<T> IndexCompress<T>
where
  T: Ord + Clone,
{
  pub fn new(mut vec: Vec<T>) -> Self
  {
    vec.sort();
    vec.dedup();
    Self {
      compressed_vals: vec,
    }
  }

  pub fn get_compressed_index(&self, value: &T) -> usize
  {
    match self.compressed_vals.binary_search(value)
    {
      Ok(idx) | Err(idx) => idx,
    }
  }

  pub fn get_max_range(&self) -> usize
  {
    self.compressed_vals.len().saturating_sub(1)
  }
}
