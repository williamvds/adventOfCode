use regex::Regex;
use std::{collections::HashMap, io};

fn parse_line(line: &str) -> u32 {
    let set_re = Regex::new(r"(\d+) (\w+)(,|;|$)").unwrap();

    let mut map: HashMap<&str, u32> = HashMap::new();
    for (_, [count_str, colour, _]) in set_re.captures_iter(line).map(|c| c.extract()) {
        let count = count_str.parse::<u32>().unwrap();
        map.entry(colour)
            .and_modify(|existing_count| *existing_count = std::cmp::max(count, *existing_count))
            .or_insert(count);
    }

    *map.entry("red").or_default()
        * *map.entry("green").or_default()
        * *map.entry("blue").or_default()
}

fn main() {
    let result = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .fold(0u32, |sum, line| {
            return sum + parse_line(&line);
        });

    println!("{}", result);
}
