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
