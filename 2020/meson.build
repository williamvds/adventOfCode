project('Advent of Code 2020', 'cpp',
  default_options : ['cpp_std=c++2a'],
  )

fmt = dependency('fmt')

libaoc2020 = library(
  'aoc2020',
  'day1.cpp',
  'day2.cpp',
  'day3.cpp',
  )

executable('aoc2020',
  'main.cpp',
  include_directories: ['thirdparty'],
  link_with: libaoc2020,
  dependencies: fmt,
  )
