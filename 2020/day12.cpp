#include <istream>
#include <optional>

#include "position.hpp"

template<typename T>
constexpr auto absolute(T value) -> T {
	return value < 0 ? -value : value;
}

static_assert(absolute(-1) == 1);
static_assert(absolute(1) == 1);

class Ship {
public:
	constexpr void move(Direction direction, int length) {
		position += Position::from_direction(direction) * length;
	}

	constexpr void move(int length) { move(direction, length); }

	constexpr void move_marker(Direction direction, int length) {
		marker += Position::from_direction(direction) * length;
	}

	constexpr void move_to_marker(int length) {
		position += marker * length;
	}

	constexpr auto manhattan_distance() -> long {
		return absolute(position.x) + absolute(position.y);
	}

	constexpr void turn(int degrees) {
		direction = ::turn(direction, degrees / 90);
	}

	constexpr void turn_left(int degrees) { turn(-degrees); }
	constexpr void turn_right(int degrees) { turn(degrees); }

	constexpr void rotate_marker(int degrees) {
		marker = marker.rotate({}, to_radians(degrees));
	}

	constexpr void rotate_marker_left(int degrees) {
		rotate_marker(degrees);
	}

	constexpr void rotate_marker_right(int degrees) {
		rotate_marker(-degrees);
	}

private:
	Position position,
			 marker{10, 1};
	Direction direction = Direction::East;
};

constexpr auto parse_direction(char character) -> Direction {
	using D = ::Direction;
	switch (character) {
		case 'N': return D::North;
		case 'E': return D::East;
		case 'S': return D::South;
		case 'W': return D::West;
	}

	throw std::invalid_argument{"Invalid character for direction"};
}

auto parse_action(std::istream& stream) -> std::optional<std::pair<char, int>> {
	char action;
	if (!(stream >> action))
		return std::nullopt;

	int length;
	if (!(stream >> length))
		return std::nullopt;

	return std::pair{action, length};
}

void process(std::istream& stream, Ship& ship) {
	const auto result = parse_action(stream);
	if (!result.has_value())
		return;

	const auto [action, length] = result.value();
	switch (action) {
		case 'L': ship.turn_left(length);  break;
		case 'R': ship.turn_right(length); break;
		case 'F': ship.move(length); break;
		default:  ship.move(parse_direction(action), length); break;
	}
}

void process_part2(std::istream& stream, Ship& ship) {
	const auto result = parse_action(stream);
	if (!result.has_value())
		return;

	const auto [action, length] = result.value();
	switch (action) {
		case 'L': ship.rotate_marker_left(length);  break;
		case 'R': ship.rotate_marker_right(length); break;
		case 'F': ship.move_to_marker(length); break;
		default:  ship.move_marker(parse_direction(action), length); break;
	}
}

auto day12(std::istream& stream) -> long {
	Ship ship;

	while (!stream.eof()) {
		process(stream, ship);
	}

	return ship.manhattan_distance();
}

auto day12Part2(std::istream& stream) -> long {
	Ship ship;

	while (!stream.eof()) {
		process_part2(stream, ship);
	}

	return ship.manhattan_distance();
}
