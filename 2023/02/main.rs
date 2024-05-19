use std::io;
use regex::Regex;
use phf::{phf_map};

static AVAILABLE_CUBES: phf::Map<&str, u32> = phf_map! {
    "red" => 12,
    "green" => 13,
    "blue" => 14,
};

fn parse_line(line: &str) -> Option<u32> {
    let game_re = Regex::new(r"Game (\d+): ").unwrap();

    let set_re = Regex::new(r"(\d+) (\w+)(,|;|$)").unwrap();
    let game_number = game_re.captures(line).unwrap()[1].parse::<u32>().unwrap();
    for (_, [count, colour, _]) in set_re.captures_iter(line).map(|c| c.extract()) {
        if count.parse::<u32>().unwrap() > AVAILABLE_CUBES[colour] {
            return None;
        }
    }

    Some(game_number)
}

fn main() {
    let result = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .fold(0u32, |sum, line| {
            return sum + parse_line(&line).unwrap_or(0);
        });

    println!("{}", result);
}
