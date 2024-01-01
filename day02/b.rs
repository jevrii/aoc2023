fn calc(s: &str) -> i32 {
    let games = s.split(":").collect::<Vec<&str>>()[1].split(";");
    let mut r = 0;
    let mut g = 0;
    let mut b = 0;
    for game in games {
        let mut cur_r = 0;
        let mut cur_g = 0;
        let mut cur_b = 0;
        let items = game.split(",");
        for item in items {
            let cnt_and_color = item.split(" ").collect::<Vec<&str>>();
            let cnt = cnt_and_color[1].parse::<i32>().unwrap();
            if cnt_and_color[2] == "red" {
                cur_r += cnt;
            }
            if cnt_and_color[2] == "green" {
                cur_g += cnt;
            }
            if cnt_and_color[2] == "blue" {
                cur_b += cnt;
            }
        }
        r = std::cmp::max(r, cur_r);
        g = std::cmp::max(g, cur_g);
        b = std::cmp::max(b, cur_b);
    }
    return r * g * b;
}

fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let mut ans = 0;
    for i in 0..lines.len() {
        let line = lines[i];
        ans += calc(line);
        // println!("{} {}", i, line);
    }
    println!("{}", ans);
}
