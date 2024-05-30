use core::ops::RangeInclusive;
use lazy_static::lazy_static;
use regex::Regex;
use std::{collections::HashSet, io};

#[derive(Hash, PartialEq, Eq, Clone, Debug, Copy)]
struct Symbol {
    x: usize,
    y: usize,
}

impl Symbol {
    fn adjacent_to(self, number: &Number) -> bool {
        number.column_range.contains(&self.x) && number.row_range.contains(&self.y)
    }
}

#[derive(Hash, PartialEq, Eq, Clone, Debug)]
struct Number {
    value: usize,
    column_range: RangeInclusive<usize>,
    row_range: RangeInclusive<usize>,
}

type SymbolNumbers = Vec<(Symbol, HashSet<Number>)>;

lazy_static! {
    static ref NUMBER_RE: Regex = Regex::new(r"(\d+)").unwrap();
    static ref SYMBOL_RE: Regex = Regex::new(r"(\*)").unwrap();
}

fn get_numbers(line: &str, row: usize) -> Vec<Number> {
    NUMBER_RE
        .captures_iter(line)
        .map(|c| c.get(1).unwrap())
        .map(|c| Number {
            value: c.as_str().parse::<usize>().unwrap(),
            column_range: RangeInclusive::new(
                c.range().start.saturating_sub(1),
                c.range().end,
            ),
            row_range: RangeInclusive::new(row.saturating_sub(1), row.saturating_add(1)),
        })
        .collect()
}

fn get_symbols(line: &str, row: usize) -> SymbolNumbers {
    SYMBOL_RE
        .captures_iter(line)
        .map(|c| {
            (
                Symbol {
                    x: c.get(1).unwrap().range().start,
                    y: row,
                },
                HashSet::new(),
            )
        })
        .collect()
}

fn update_adjacent_numbers(numbers: &[Number], symbols: &mut SymbolNumbers) {
    numbers.into_iter().for_each(|n| {
        symbols
            .into_iter()
            .filter(|(s, _)| s.adjacent_to(&n))
            .for_each(|(_, ns)| _ = ns.insert(n.clone()))
    });
}

fn incremental_parse_numbers(
    state: (Vec<Number>, SymbolNumbers),
    line: &str,
    row: usize,
) -> (Vec<Number>, SymbolNumbers) {
    let (previous_numbers, mut symbols) = state;
    let numbers = get_numbers(line, row);

    symbols.append(&mut get_symbols(line, row));
    update_adjacent_numbers(&previous_numbers, &mut symbols);
    update_adjacent_numbers(&numbers, &mut symbols);

    #[cfg(debug_assertions)]
    {
        println!("symbols: {:?}\n", symbols);
    };

    (numbers, symbols)
}

fn main() {
    let (_, symbols) = io::stdin()
        .lines()
        .map(Result::unwrap)
        .filter(|s| !s.is_empty())
        .enumerate()
        .fold((Vec::new(), SymbolNumbers::new()), |state, (n, line)| {
            incremental_parse_numbers(state, line.as_str(), n)
        });

    let result: usize = symbols
        .into_iter()
        .map(|(_, ns)| ns)
        .filter(|ns| ns.len() == 2)
        .map(|ns| {
            let mut iter = ns.iter();
            iter.next().unwrap().value * iter.next().unwrap().value
        })
        .sum();

    println!("{}", result);
}
