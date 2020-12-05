#include <array>
#include <istream>

int day1(std::istream&);

constexpr auto days = std::to_array({
	&day1,
});
