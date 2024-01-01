use std::collections::HashMap;

struct Choice {
    left: Box<str>,
    right: Box<str>,
}

fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let mut edges = HashMap::new();

    for i in 2..lines.len() {
        let line = lines[i];
        let src = &line[0..3];
        let left = &line[7..10];
        let right = &line[12..15];

        edges.insert(
            src,
            Choice {
                left: left.into(),
                right: right.into(),
            },
        );
    }

    let mut ans = 0;
    let mut ok = false;
    let mut cur: &str = "AAA";

    while true {
        for c in lines[0].chars() {
            if c == 'L' {
                cur = &edges.get(cur).unwrap().left;
            } else {
                cur = &edges.get(cur).unwrap().right;
            }
            ans += 1;
            if cur == "ZZZ" {
                ok = true;
                break;
            }
        }
        if ok {
            break;
        }
    }

    println!("{}", ans);
}
