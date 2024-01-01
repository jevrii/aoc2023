fn is_symbol(c: char) -> bool {
    if c == '.' {
        return false;
    }
    if c.is_digit(10) {
        return false;
    }
    return true;
}

fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let mut inside_number = false;
    let mut cur_num = 0;
    let mut has_symbol = false;
    let mut ans = 0;

    for row in 0..lines.len() {
        for col in 0..lines[row].len() {
            let c = lines[row].chars().nth(col).unwrap();

            if c.is_digit(10) {
                if row > 0 {
                    let check = lines[row - 1].chars().nth(col).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if row + 1 < lines.len() {
                    let check = lines[row + 1].chars().nth(col).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if col > 0 {
                    let check = lines[row].chars().nth(col - 1).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if col + 1 < lines[row].len() {
                    let check = lines[row].chars().nth(col + 1).unwrap();
                    has_symbol |= is_symbol(check);
                }

                if row > 0 && col > 0 {
                    let check = lines[row - 1].chars().nth(col - 1).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if row + 1 < lines.len() && col > 0 {
                    let check = lines[row + 1].chars().nth(col - 1).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if row > 0 && col + 1 < lines[row].len() {
                    let check = lines[row - 1].chars().nth(col + 1).unwrap();
                    has_symbol |= is_symbol(check);
                }
                if row + 1 < lines.len() && col + 1 < lines[row].len() {
                    let check = lines[row + 1].chars().nth(col + 1).unwrap();
                    has_symbol |= is_symbol(check);
                }

                cur_num = cur_num * 10 + c.to_digit(10).unwrap();
                inside_number = true;

                if col == lines[row].len() - 1 {
                    if inside_number {
                        if has_symbol {
                            ans += cur_num;
                            println!("{}", cur_num);
                        }
                    }
                    inside_number = false;
                    has_symbol = false;
                    cur_num = 0;
                }
            } else {
                if inside_number {
                    if has_symbol {
                        ans += cur_num;
                        println!("{}", cur_num);
                    }
                }
                inside_number = false;
                has_symbol = false;
                cur_num = 0;
            }
        }
    }
    println!("{}", ans);
}
