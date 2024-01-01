use std::cmp;
use std::collections::HashSet;

fn main() {
    let lines = include_str!("input.txt").split("\n");
    let mut ans: u64 = 0;
    let mut cnt = [1u64; 250];
    let mut idx: usize = 1;
    for line in lines {
        let str_splitted = line.split_whitespace().collect::<Vec<&str>>();
        let mut ints = HashSet::new();
        for i in 2..12 {
            ints.insert(str_splitted[i].parse::<i32>().unwrap());
        }
        let mut c: usize = 0;
        for i in 13..str_splitted.len() {
            let x = str_splitted[i].parse::<i32>().unwrap();
            if ints.contains(&x) {
                c += 1;
            }
        }
        for i in idx + 1..cmp::min(250, idx + 1 + c) {
            cnt[i] += cnt[idx] as u64;
        }
        ans += cnt[idx];
        idx += 1;
    }
    println!("{}", ans);
}
