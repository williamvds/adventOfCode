use core::ops::Range;
use regex::Regex;
use std::{collections::HashSet, io};
use lazy_static::lazy_static;

#[derive(Hash, PartialEq, Eq, Clone, Debug)]
struct Number {
    value: u32,
    range: Range<usize>,
}

lazy_static! {
    static ref NUMBER_RE: Regex = Regex::new(r"(\d+)").unwrap();
    static ref SYMBOL_RE: Regex = Regex::new(r"([^\d\.])").unwrap();
}

fn get_numbers(line: &str) -> HashSet<Number> {
    return NUMBER_RE
        .captures_iter(line)
        .map(|c| c.get(1).unwrap())
        .map(|c| Number {
            value: c.as_str().parse::<u32>().unwrap(),
            range: Range {
                start: c.range().start.saturating_sub(1),
                end: c.range().end.saturating_add(1),
            },
        })
        .collect();
}

fn get_symbols(line: &str) -> Vec<usize> {
    return SYMBOL_RE
        .captures_iter(line)
        .map(|c| c.get(1).unwrap().range().start)
        .collect();
}

fn find_adjacent_numbers(numbers: &HashSet<Number>, symbols: &Vec<usize>) -> HashSet<Number> {
    return numbers
        .into_iter()
        .filter_map(|n| {
            if symbols.into_iter().any(|s| n.range.contains(&s)) {
                Some(n.clone())
            } else {
                None
            }
        })
        .collect();
}

fn parse_line(line: &str) -> (Vec<u32>, HashSet<Number>, Vec<usize>) {
    let numbers = get_numbers(line);
    let symbols = get_symbols(line);
    let adjacent = find_adjacent_numbers(&numbers, &symbols);

    (
        adjacent.iter().map(|n| n.value).collect(),
        numbers.difference(&adjacent).cloned().collect(),
        symbols,
    )
}

fn main() {
    let result = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .fold(0u32, |sum, line| {
            let (part_numbers, line_numbers, line_symbol_locations) = parse_line(line.as_str());
            println!("Found: {:?}, line_numbers={:?}, line_symbol_locations={:?}", part_numbers, line_numbers, line_symbol_locations);
            return sum + part_numbers.iter().sum::<u32>();
        });

    println!("{}", result);
}
