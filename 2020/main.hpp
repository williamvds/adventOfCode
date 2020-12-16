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

using Task = std::function<int(std::istream&)>;

auto days = std::map<std::string_view, Task>{
	{"1",   &day1},
	{"1.2", &day1Part2},
	{"2",   &day2},
	{"2.2", &day2Part2},
	{"3",   &day3},
	{"3.2", &day3Part2},
	{"4",   &day4},
};
