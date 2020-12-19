#include <algorithm>
#include <istream>
#include <set>

constexpr auto rowUpper = 'B';
constexpr auto rowLower = 'F';
constexpr auto columnUpper = 'R';
constexpr auto columnLower = 'L';

struct Range {
	unsigned lower, upper;
	constexpr auto lowerHalf() const -> Range { return Range{lower, upper - half()}; }
	constexpr auto upperHalf() const -> Range { return Range{lower + half(), upper}; }
	constexpr auto half() const -> unsigned { return (upper - lower) / 2 + 1; }
};

struct Seat {
	unsigned row, column;
	constexpr auto id() const -> unsigned { return row * 8 + column; }
};

auto seat_from_partition(std::string_view sequence) -> Seat {
	auto rowRange = Range{0, 127};
	auto columnRange = Range{0, 7};

	for (auto character : sequence) {
		switch (character) {
			case rowUpper: rowRange = rowRange.upperHalf(); break;
			case rowLower: rowRange = rowRange.lowerHalf(); break;
			case columnUpper: columnRange = columnRange.upperHalf(); break;
			case columnLower: columnRange = columnRange.lowerHalf(); break;
		}
	}

	return Seat{rowRange.lower, columnRange.lower};
}

int day5(std::istream& stream) {
	unsigned maxId = 0;

	std::string line;
	while (stream >> line) {
		const auto seat = seat_from_partition(line);
		maxId = std::max(maxId, seat.id());
	}

	return maxId;
}

int day5Part2(std::istream& stream) {
	std::set<unsigned> seatIds;

	std::string line;
	while (stream >> line) {
		const auto seat = seat_from_partition(line);
		seatIds.insert(seat.id());
	}

	const auto found = std::adjacent_find(seatIds.begin(), seatIds.end(),
		[](unsigned left, unsigned right) { return right - left > 1; });

	return *found + 1;
}
