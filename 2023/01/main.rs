use std::io;

fn main() {
    let result = io::stdin().lines().fold(0u32, |sum, line| {
        let result = line.unwrap();

        if result.is_empty() {
            return sum;
        }

        let is_digit = |c: char| c.is_digit(10);
        let first_pos = result.find(is_digit).unwrap();
        let last_pos = result.rfind(is_digit).unwrap();

        let joined = String::from_utf8(vec![
            result.as_bytes()[first_pos],
            result.as_bytes()[last_pos],
        ])
        .unwrap();

        return sum + joined.parse::<u32>().unwrap();
    });

    println!("{}", result);
}
