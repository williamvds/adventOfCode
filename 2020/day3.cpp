#include <array>
#include <functional>
#include <istream>
#include <limits>

constexpr char tree = '#';

struct Velocity {
	unsigned x, y;
};

int slope_collisions(std::istream& stream, Velocity velocity) {
	std::string row;
	size_t column = 0, total = 0;

	const auto newline = stream.widen('\n');
	while (stream >> row) {
		if (row[column] == tree)
			total++;

		column = (column + velocity.x) % row.length();

		for (size_t i = 0; i < velocity.y; i++)
			stream.ignore(
				std::numeric_limits<std::streamsize>::max(), newline);
	}

	stream.clear();
	stream.seekg(0);
	return total;
}

int day3(std::istream& stream) {
	return slope_collisions(stream, {3, 1});
}

int day3Part2(std::istream& stream) {
	constexpr auto velocities = std::to_array<const Velocity>({
		{1, 1},
		{3, 1},
		{5, 1},
		{7, 1},
		{1, 2},
	});

	return std::apply(
		[&stream](auto... velocity) {
			return (slope_collisions(stream, velocity) * ...); }, velocities);
}
