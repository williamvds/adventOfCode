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
                Some((int, string.len()))
            } else {
                None
            }
        })
        .map_or_else(
            || (None, 1),
            |(&int, length)| (Some(int), length),
        );
}

fn parse_line(slice: &str) -> u32 {
    // TODO: This parsing loop is an absolute mess, and the reverse one is even worse

    let mut first_digit: Option<u32> = None;
    let mut start_slice = slice;
    loop {
        let (maybe_digit, length) = parse_digit(start_slice);
        if let Some(i) = maybe_digit {
            first_digit = Some(i);
            break;
        }
        start_slice = &start_slice[length..];
    }

    let mut last_digit: Option<u32> = None;
    let mut end_index = slice.len() - 1;
    loop {
        let end_slice = &slice[end_index..];
        let (maybe_digit, length) = parse_digit(end_slice);
        if let Some(i) = maybe_digit {
            last_digit = Some(i);
            break;
        }
        end_index -= length;
    }

    return (first_digit.unwrap() * 10) + last_digit.unwrap();
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
