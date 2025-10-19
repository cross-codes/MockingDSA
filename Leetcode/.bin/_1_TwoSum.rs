#![allow(dead_code)]
struct Solution;

use std::collections::HashMap;

impl Solution {
  pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut map: HashMap<i32, i32> = HashMap::new();
    for (i, &x) in nums.iter().enumerate() {
      let c = target - x;
      if let Some(&c_idx) = map.get(&c) {
        return vec![c_idx, i as i32];
      }

      map.insert(x, i as i32);
    }

    unreachable!()
  }
}

fn main() {}
