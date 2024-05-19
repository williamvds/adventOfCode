use std::io;

fn main() {
    let result = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .fold(0u32, |sum, line| {
            let is_digit = |c: char| c.is_digit(10);
            let first_pos = line.find(is_digit).unwrap();
            let last_pos = line.rfind(is_digit).unwrap();

            let bytes = line.as_bytes();
            let joined = String::from_utf8(vec![bytes[first_pos], bytes[last_pos]]).unwrap();

            return sum + joined.parse::<u32>().unwrap();
        });

    println!("{}", result);
}
