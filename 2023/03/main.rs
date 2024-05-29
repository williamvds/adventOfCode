use core::ops::Range;
use lazy_static::lazy_static;
use regex::Regex;
use std::{collections::HashSet, io};

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
    numbers
        .into_iter()
        .filter_map(|n| {
            if symbols.into_iter().any(|s| n.range.contains(&s)) {
                Some(n.clone())
            } else {
                None
            }
        })
        .collect()
}

fn incremental_parse_numbers(
    state: (u32, HashSet<Number>, Vec<usize>),
    line: &str,
) -> (u32, HashSet<Number>, Vec<usize>) {
    let (sum, previous_unmatched_numbers, previous_symbols) = &state;
    let numbers = get_numbers(line);
    let symbols = get_symbols(line);

    #[cfg(debug_assertions)]
    {
        println!("numbers: {:?}, symbols={:?}", numbers, symbols);
    };

    let part_numbers = find_adjacent_numbers(&numbers, &previous_symbols)
        .union(&find_adjacent_numbers(&numbers, &symbols))
        .cloned()
        .collect();

    let previous_part_numbers = find_adjacent_numbers(&previous_unmatched_numbers, &symbols);

    let unmatched_numbers = numbers.difference(&part_numbers).cloned().collect();

    #[cfg(debug_assertions)]
    {
        println!(
            "matched previous numbers: {:?}, matched numbers: {:?}, unmatched numbers={:?}\n",
            previous_part_numbers, part_numbers, unmatched_numbers
        );
    };

    return (
        sum + part_numbers
            .union(&previous_part_numbers)
            .map(|n| n.value)
            .sum::<u32>(),
        unmatched_numbers,
        symbols,
    );
}

fn main() {
    let lines: Vec<String> = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .collect();

    let (result, _, _) = lines.iter().map(|l| l.as_str()).fold(
        (0u32, HashSet::new(), Vec::new()),
        incremental_parse_numbers,
    );

    println!("{}", result);
}
