fn calc(s: &str)->bool {
    let games = s.split(":").collect::<Vec<&str>>()[1].split(";");
    for game in games {

        let items = game.split(",");
        for item in items {
            let mut r = 0;
            let mut g = 0;
            let mut b = 0;

            let cnt_and_color = item.split(" ").collect::<Vec<&str>>();
            let cnt = cnt_and_color[1].parse::<i32>().unwrap();
            if cnt_and_color[2] == "red" {
                r += cnt;
            }
            if cnt_and_color[2] == "green" {
                g += cnt;
            }
            if cnt_and_color[2] == "blue" {
                b += cnt;
            }

            if r > 12 || g > 13 || b > 14 {
                return false;
            }
        }
    }
    return true;
}

fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let mut ans = 0;
    for i in 0..lines.len() {
        let line = lines[i];
        if calc(line) {
            ans += i + 1;
        }
        // println!("{} {}", i, line);
    }
    println!("{}", ans);
}
