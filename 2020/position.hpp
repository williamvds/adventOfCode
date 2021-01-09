#pragma once

enum class Direction {
	North,
	East,
	South,
	West,
};

constexpr auto turn(Direction direction, int offset) -> Direction {
	const auto sum = static_cast<int>(direction) + offset;
	return static_cast<Direction>((sum < 0 ? sum + 4 : sum) % 4);
}

static_assert(turn(Direction::North, 1) == Direction::East);
static_assert(turn(Direction::North, -1) == Direction::West);
static_assert(turn(Direction::West, 1) == Direction::North);

struct Position {
	int x = 0, y = 0;

	constexpr Position() : x{0}, y{0} { }
	constexpr Position(int x, int y) : x{x}, y{y} { }

	constexpr auto operator +(const Position& right) const -> Position {
		return {x + right.x, y + right.y};
	}

	constexpr auto operator +=(const Position& right) -> Position& {
		*this = *this + right;
		return *this;
	}

	constexpr auto operator *(int multiplier) const -> Position {
		return {x * multiplier, y * multiplier};
	}

	constexpr auto is_in_box(int x1, int y1, int x2, int y2) const -> bool {
		return x >= x1 && y >= y1 && x <= x2 && y <= y2;
	}

	static const Position North, East, South, West;
	static constexpr auto from_direction(Direction direction) -> Position {
		using D = ::Direction;
		switch (direction) {
			case D::North: return North;
			case D::East:  return East;
			case D::South: return South;
			case D::West:  return West;
		}
	}
};

constexpr auto Position::North = Position{0, 1},
			   Position::East  = Position{1, 0},
			   Position::South = Position{0, -1},
			   Position::West  = Position{-1, 0};
