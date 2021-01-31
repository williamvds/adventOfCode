#include <functional>
#include <istream>
#include <map>
#include <string_view>

long day1(std::istream&);
long day1Part2(std::istream&);

long day2(std::istream&);
long day2Part2(std::istream&);

long day3(std::istream&);
long day3Part2(std::istream&);

long day4(std::istream&);
long day4Part2(std::istream&);

long day5(std::istream&);
long day5Part2(std::istream&);

long day6(std::istream&);
long day6Part2(std::istream&);

long day7(std::istream&);
long day7Part2(std::istream&);

long day8(std::istream&);
long day8Part2(std::istream&);

long day9(std::istream&);
long day9Part2(std::istream&);

long day10(std::istream&);
long day10Part2(std::istream&);

long day11(std::istream&);
long day11Part2(std::istream&);

long day12(std::istream&);
long day12Part2(std::istream&);

long day13(std::istream&);
long day13Part2(std::istream&);

long day14(std::istream&);
long day14Part2(std::istream&);

long day15(std::istream&);

using Task = std::function<long(std::istream&)>;

auto days = std::map<std::string_view, Task>{
	{"1",    &day1},
	{"1.2",  &day1Part2},
	{"2",    &day2},
	{"2.2",  &day2Part2},
	{"3",    &day3},
	{"3.2",  &day3Part2},
	{"4",    &day4},
	{"4.2",  &day4Part2},
	{"5",    &day5},
	{"5.2",  &day5Part2},
	{"6",    &day6},
	{"6.2",  &day6Part2},
	{"7",    &day7},
	{"7.2",  &day7Part2},
	{"8",    &day8},
	{"8.2",  &day8Part2},
	{"9",    &day9},
	{"9.2",  &day9Part2},
	{"10",   &day10},
	{"10.2", &day10Part2},
	{"11",   &day11},
	{"11.2", &day11Part2},
	{"12",   &day12},
	{"12.2", &day12Part2},
	{"13",   &day13},
	{"13.2", &day13Part2},
	{"14",   &day14},
	{"14.2", &day14Part2},
	{"15",   &day15},
};
