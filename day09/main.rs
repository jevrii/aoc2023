fn factorial(n: u32) -> u64 {
    let mut ret: u64 = 1;
    for i in 1u64..n as u64 + 1u64 {
        ret *= i;
    }
    return ret;
}

fn ncr(n: i32, mut r: i32) -> i64 {
    let mut ret: i64 = 1;
    // if r < n / 2 {
    //     r = n - r;
    // }
    // for i in r + 1..n + 1 {
    //     ret *= i as u64;
    // }
    // for i in 1..n - r + 1 {
    //     ret /= i as u64;
    // }
    // return ret.into();
    // // return factorial(n) / factorial(r) / factorial(n - r);
    if r == 0 {
        return 1;
    }
    for i in n - r + 1..n + 1 {
        ret *= i as i64;
    }
    for i in 1..r + 1 {
        ret /= i as i64;
    }
    return ret;
}

fn main() {
    let lines = include_str!("input.txt").split("\n");
    let mut total = 0;
    for line in lines {
        let mut diag = Vec::<i64>::new();
        let mut cur = Vec::<i32>::new();
        for int_str in line.split(" ") {
            cur.push(int_str.parse::<i32>().unwrap());
        }
        while true {
            diag.push(cur[0] as i64);
            let mut nxt = Vec::<i32>::new();
            for i in 0..cur.len() - 1 {
                nxt.push(cur[i + 1] - cur[i]);
            }
            if !nxt.iter().any(|&i| i != 0) {
                break;
            }
            cur = nxt;
        }

        // println!("{}", line.split(" ").count());

        let mut ans = 0;
        for i in 0..diag.len() {
            // print!("{} {}\n", line.split(" ").count() as u32, i as u32);
            // ans += diag[i] * ncr(line.split(" ").count() as i32, i as i32) as i64;
            // ans += diag[i] * ncr(4, i as i32) as i64;
            // ans += diag[i] * ncr(202300, i as i32) as i64; # day 21
            // print!("{} {}\n", i, ncr(-1, i as i32));
            ans += diag[i] * ncr(-1, i as i32) as i64;
        }
        // print!("\n");

        // for x in diag {
        //     print!("{} ", x);
        // }
        // println!("{}", ans);
        total += ans;
    }
    println!("{}", total);
}
