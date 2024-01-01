fn main() {
    let time: u64 = 49787980;
    let dist: u64 = 298118510661181;

    let mut ans = 0;
    for t in 1..time {
        if (time - t) * t > dist {
            ans += 1;
        }
    }
    println!("{}", ans);
}
