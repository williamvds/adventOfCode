#include <istream>
#include <optional>

#include "position.hpp"

template<typename T>
constexpr auto absolute(T value) -> T {
	return value < 0 ? value * -1 : value;
}

static_assert(absolute(-1) == 1);
static_assert(absolute(1) == 1);

class Ship {
public:
	constexpr void move(Direction direction, int length) {
		position += Position::from_direction(direction) * length;
	}

	constexpr void move(int length) { move(direction, length); }

	constexpr auto manhattan_distance() -> long {
		return absolute(position.x) + absolute(position.y);
	}

	constexpr void turn(int degrees) {
		direction = ::turn(direction, degrees / 90);
	}

	constexpr void turn_left(int degrees) { turn(-degrees); }
	constexpr void turn_right(int degrees) { turn(degrees); }

private:
	Position position;
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

void parse_action(std::istream& stream, Ship& ship) {
	char action;

	if (!(stream >> action))
		return;

	int length;
	if (!(stream >> length))
		return;

	switch (action) {
		case 'L': ship.turn_left(length);  break;
		case 'R': ship.turn_right(length); break;
		case 'F': ship.move(length); break;
		default:  ship.move(parse_direction(action), length); break;
	}
}

auto day12(std::istream& stream) -> long {
	Ship ship;

	while (!stream.eof()) {
		parse_action(stream, ship);
	}

	return ship.manhattan_distance();
}
