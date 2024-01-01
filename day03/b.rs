fn is_symbol(c: char) -> bool {
    return c == '*';
}

fn process(row: i32, col: i32, star_r: &mut i32, star_c: &mut i32, lines: &Vec<&str>) -> bool {
    if row < 0 || row >= lines.len() as i32 {
        return false;
    }
    if col < 0 || col >= lines[row as usize].len() as i32 {
        return false;
    }
    let c = lines[row as usize].chars().nth(col as usize).unwrap();
    if is_symbol(c) {
        *star_r = row;
        *star_c = col;
        return true;
    }
    return false;
}

fn main() {
    let lines = include_str!("input.txt").split("\n").collect::<Vec<&str>>();
    let mut inside_number = false;
    let mut cur_num = 0;
    let mut has_symbol = false;
    let mut star_r = 0;
    let mut star_c = 0;
    let mut ans = 0;
    let mut ratio = [[0u32; 200]; 200];
    let mut cnt = [[0u32; 200]; 200];

    for row in 0..lines.len() as i32 {
        for col in 0..lines[row as usize].len() as i32 {
            let c = lines[row as usize].chars().nth(col as usize).unwrap();

            if c.is_digit(10) {
                has_symbol |= process(row - 1, col, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row + 1, col, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row, col - 1, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row, col + 1, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row - 1, col - 1, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row - 1, col + 1, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row + 1, col - 1, &mut star_r, &mut star_c, &lines);
                has_symbol |= process(row + 1, col + 1, &mut star_r, &mut star_c, &lines);

                cur_num = cur_num * 10 + c.to_digit(10).unwrap();
                inside_number = true;

                if col as usize == lines[row as usize].len() - 1 {
                    if inside_number {
                        if has_symbol {
                            // println!(
                            //     "{} {} {} {}",
                            //     cur_num, star_r, star_c, ratio[star_r as usize][star_c as usize]
                            // );
                            if ratio[star_r as usize][star_c as usize] == 0 {
                                ratio[star_r as usize][star_c as usize] = cur_num;
                            } else {
                                ratio[star_r as usize][star_c as usize] *= cur_num;
                            }
                            cnt[star_r as usize][star_c as usize] += 1;
                        }
                    }
                    inside_number = false;
                    has_symbol = false;
                    cur_num = 0;
                }
            } else {
                if inside_number {
                    if has_symbol {
                        // println!(
                        //     "{} {} {} {}",
                        //     cur_num, star_r, star_c, ratio[star_r as usize][star_c as usize]
                        // );
                        if ratio[star_r as usize][star_c as usize] == 0 {
                            ratio[star_r as usize][star_c as usize] = cur_num;
                        } else {
                            ratio[star_r as usize][star_c as usize] *= cur_num;
                        }
                        cnt[star_r as usize][star_c as usize] += 1;
                    }
                }
                inside_number = false;
                has_symbol = false;
                cur_num = 0;
            }
        }
    }

    for row in 0..200 {
        for col in 0..200 {
            if cnt[row][col] == 2 {
                // println!("{}", ratio[row][col]);
                ans += ratio[row][col];
            }
        }
    }
    println!("{}", ans);
}
