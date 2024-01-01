use std::collections::HashSet;

fn main() {
    let lines = include_str!("input.txt").split("\n");
    let mut ans = 0;
    for line in lines {
        let str_splitted = line.split_whitespace().collect::<Vec<&str>>();
        let mut ints = HashSet::new();
        for i in 2..12 {
            ints.insert(str_splitted[i].parse::<i32>().unwrap());
        }
        let mut cnt = 0;
        let mut add = 0;
        for i in 13..str_splitted.len() {
            let x = str_splitted[i].parse::<i32>().unwrap();
            if ints.contains(&x) {
                if cnt == 0 {
                    add = 1;
                } else {
                    add *= 2;
                }
                cnt += 1;
            }
        }
        ans += add;
    }
    println!("{}", ans);
}
