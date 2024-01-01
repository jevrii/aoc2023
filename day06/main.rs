fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let times_str = lines[0].split_whitespace().collect::<Vec<&str>>();
    let mut times: Vec<u32> = Vec::new();
    for i in 1..times_str.len() {
        times.push(times_str[i].parse::<u32>().unwrap());
    }
    let dists_str = lines[1].split_whitespace().collect::<Vec<&str>>();
    let mut dists: Vec<u32> = Vec::new();
    for i in 1..dists_str.len() {
        dists.push(dists_str[i].parse::<u32>().unwrap());
    }

    let mut ans = 1;
    for i in 0..times.len() {
        let mut cnt = 0;
        for t in 1..times[i] {
            if (times[i] - t) * t > dists[i] {
                cnt += 1;
            }
        }
        if cnt == 0 {
            println!("0");
            return;
        }
        ans *= cnt;
    }
    println!("{}", ans);
}
