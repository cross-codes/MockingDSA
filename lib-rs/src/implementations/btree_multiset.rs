use std::collections::{btree_map, BTreeMap};
use std::ops::RangeBounds;

pub struct BTreeMultiset<T: Ord> {
  map: BTreeMap<T, usize>,
  size: usize,
}

pub struct Range<'a, T: 'a> {
  map_range: btree_map::Range<'a, T, usize>,
  cur_val: Option<&'a T>,
  cur_cnt: usize,
  cur_val_b: Option<&'a T>,
  cur_cnt_b: usize,
}

impl<'a, T: Ord> Iterator for Range<'a, T> {
  type Item = &'a T;

  fn next(&mut self) -> Option<Self::Item> {
    if self.cur_cnt > 0 {
      self.cur_cnt -= 1;
      return self.cur_val;
    }

    if let Some((val, &cnt)) = self.map_range.next() {
      self.cur_val = Some(val);
      self.cur_cnt = cnt - 1;
      return self.cur_val;
    }

    None
  }
}

impl<'a, T: Ord> DoubleEndedIterator for Range<'a, T> {
  fn next_back(&mut self) -> Option<Self::Item> {
    if self.cur_cnt_b > 0 {
      self.cur_cnt_b -= 1;
      return self.cur_val_b;
    }

    if let Some((val, &cnt)) = self.map_range.next_back() {
      self.cur_val_b = Some(val);
      self.cur_cnt_b = cnt - 1;
      return self.cur_val_b;
    }

    None
  }
}

impl<T: Ord> BTreeMultiset<T> {
  pub fn new() -> Self {
    BTreeMultiset {
      map: BTreeMap::new(),
      size: 0,
    }
  }

  pub fn insert(&mut self, value: T) -> bool {
    let cnt = self.map.entry(value).or_insert(0);
    *cnt += 1;
    self.size += 1;

    true
  }

  pub fn remove_one(&mut self, value: &T) -> bool {
    if let Some(cnt) = self.map.get_mut(value) {
      *cnt -= 1;
      if *cnt == 0 {
        self.map.remove(value);
      }

      self.size -= 1;
      return true;
    }

    false
  }

  pub fn remove_all(&mut self, value: &T) -> bool {
    if let Some(cnt) = self.map.remove(value) {
      self.size -= cnt;
      return true;
    }

    false
  }

  pub fn len(&self) -> usize {
    self.size
  }

  pub fn contains(&self, value: &T) -> bool {
    self.map.contains_key(value)
  }

  pub fn is_empty(&self) -> bool {
    self.size == 0
  }

  pub fn count(&self, value: &T) -> usize {
    self.map.get(value).cloned().unwrap_or(0)
  }

  pub fn range<R>(&self, range: R) -> Range<'_, T>
  where
    R: RangeBounds<T>,
  {
    Range {
      map_range: self.map.range(range),
      cur_val: None,
      cur_cnt: 0,
      cur_val_b: None,
      cur_cnt_b: 0,
    }
  }
}
