project('Advent of Code 2020', 'cpp',
  default_options : ['cpp_std=c++2a'],
  )

fmt = dependency('fmt')

libaoc2020 = library(
  'aoc2020',
  'day1.cpp',
  'day2.cpp',
  'day3.cpp',
  'day4.cpp',
  'day5.cpp',
  'day6.cpp',
  'day7.cpp',
  'day8.cpp',
  'day9.cpp',
  'day10.cpp',
  'day11.cpp',
  'day12.cpp',
  'day13.cpp',
  'day14.cpp',
  'day15.cpp',
  include_directories: ['thirdparty'],
  )

executable('aoc2020',
  'main.cpp',
  include_directories: ['thirdparty'],
  link_with: libaoc2020,
  dependencies: fmt,
  )
