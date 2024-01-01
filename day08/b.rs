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
    let mut cur: Vec<&str> = Vec::<&str>::new();

    for i in 2..lines.len() {
        let line = lines[i];
        let src = &line[0..3];

        if src.chars().nth(2).unwrap() == 'A' {
            cur.push(src);
        }
    }

    while true {
        for c in lines[0].chars() {
            let mut nxt: Vec<&str> = Vec::<&str>::new();
            for node in cur {
                let mut new_node: &str;
                if c == 'L' {
                    new_node = &edges.get(node).unwrap().left;
                } else {
                    new_node = &edges.get(node).unwrap().right;
                }
                nxt.push(new_node);
            }

            ans += 1;
            cur = nxt;

            if cur
                .iter()
                .filter(|&s| s.chars().nth(2).unwrap() == 'Z')
                .count()
                == cur.len()
            {
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
