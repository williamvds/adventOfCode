#include <functional>
#include <istream>
#include <map>
#include <string_view>

int day1(std::istream&);
int day1Part2(std::istream&);

int day2(std::istream&);
int day2Part2(std::istream&);

int day3(std::istream&);
int day3Part2(std::istream&);

int day4(std::istream&);
int day4Part2(std::istream&);

int day5(std::istream&);
int day5Part2(std::istream&);

int day6(std::istream&);
int day6Part2(std::istream&);

int day7(std::istream&);
int day7Part2(std::istream&);

int day8(std::istream&);

using Task = std::function<int(std::istream&)>;

auto days = std::map<std::string_view, Task>{
	{"1",   &day1},
	{"1.2", &day1Part2},
	{"2",   &day2},
	{"2.2", &day2Part2},
	{"3",   &day3},
	{"3.2", &day3Part2},
	{"4",   &day4},
	{"4.2", &day4Part2},
	{"5",   &day5},
	{"5.2", &day5Part2},
	{"6",   &day6},
	{"6.2", &day6Part2},
	{"7",   &day7},
	{"7.2", &day7Part2},
	{"8",   &day8},
};
