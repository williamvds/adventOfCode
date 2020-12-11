#include <functional>
#include <istream>
#include <map>
#include <string_view>

int day1(std::istream&);
int day1Part2(std::istream&);

int day2(std::istream&);
int day2Part2(std::istream&);

using Task = std::function<int(std::istream&)>;

auto days = std::map<std::string_view, Task>{
	{"1",   &day1},
	{"1.2", &day1Part2},
	{"2",   &day2},
	{"2.2", &day2Part2},
};
