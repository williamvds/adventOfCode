use std::io;

static DIGITS: &[(&str, u32)] = &[
    ("zero", 1),
    ("one", 1),
    ("two", 2),
    ("three", 3),
    ("four", 4),
    ("five", 5),
    ("six", 6),
    ("seven", 7),
    ("eight", 8),
    ("nine", 9),
];

fn parse_digit(slice: &str) -> (Option<u32>, usize) {
    if slice.chars().next().unwrap().is_digit(10) {
        return (char::to_digit(slice.as_bytes()[0] as char, 10), 1);
    }

    return DIGITS
        .iter()
        .find_map(|(string, int)| {
            if slice.starts_with(string) {
                Option::Some((int, string.len()))
            } else {
                Option::None
            }
        })
        .map_or_else(
            || (Option::None, 1),
            |(&int, length)| (Option::Some(int), length),
        );
}

fn parse_line(slice: &str) -> u32 {
    let mut first_digit: u32 = 0;
    let mut start_slice = slice;
    loop {
        let (maybe_digit, length) = parse_digit(start_slice);
        if let Some(i) = maybe_digit {
            first_digit = i;
            break;
        }
        start_slice = &start_slice[length..];
    }

    let mut last_digit: u32 = 0;
    let mut end_index = slice.len() - 1;
    loop {
        let end_slice = &slice[end_index..];
        let (maybe_digit, length) = parse_digit(end_slice);
        println!("{} {:?} {}", end_slice, maybe_digit, length);
        if let Some(i) = maybe_digit {
            last_digit = i;
            break;
        }
        end_index -= length;
    }

    return (first_digit * 10) + last_digit;
}

fn main() {
    let result = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .fold(0u32, |sum, line| {
            return sum + parse_line(line.as_str());
        });

    println!("{}", result);
}
