#include <algorithm>
#include <array>
#include <istream>
#include <numeric>
#include <sstream>
#include <vector>

constexpr auto charFloor = '.';
constexpr auto charEmpty = 'L';
constexpr auto charOccupied = '#';

enum class State {
	Floor,
	Empty,
	Occupied,
};

struct Position {
	int x, y;

	constexpr auto operator +(const Position& right) const -> Position {
		return {x + right.x, y + right.y};
	}

	constexpr auto is_in_box(int x1, int y1, int x2, int y2) const -> bool {
		return x >= x1 && y >= y1 && x <= x2 && y <= y2;
	}
};

using Row = std::vector<State>;
using Layout = std::vector<Row>;

constexpr auto parse_position(char character) -> State {
	using S = State;
	switch (character) {
		case charFloor:    return S::Floor;
		case charEmpty:    return S::Empty;
		case charOccupied: return S::Occupied;
	}
	throw std::invalid_argument{"Attempted to parse invalid position character"};
}

auto parse_layout(std::istream& stream) -> Layout {
	Layout layout;

	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty())
			break;

		std::stringstream lineStream{line};
		Row row;

		char character;
		while (lineStream >> character) {
			row.push_back(parse_position(character));
		}

		layout.push_back(std::move(row));
	}

	return layout;
}

constexpr auto find_adjacent(Position position) {
	const auto offsets = std::to_array<Position>({
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
		{0, -1},
		{1, -1},
	});

	auto positions = std::array{offsets};
	std::transform(positions.begin(), positions.end(), positions.begin(),
		[&](const auto& offset) { return position + offset; });

	return positions;
}

constexpr auto apply_rule(const Layout& layout, const Position& pos) -> State {
	auto rows = layout.size();
	auto columns = layout.front().size();

	const auto adjacents = find_adjacent(pos);
	const auto occupied = std::count_if(adjacents.begin(), adjacents.end(),
		[&](const auto& pos) {
			return pos.is_in_box(0, 0, columns - 1, rows - 1) &&
				layout.at(pos.y).at(pos.x) == State::Occupied;
		});

	const auto currentState = layout.at(pos.y).at(pos.x);
	switch (currentState) {
		case State::Empty: {
			if (occupied == 0)
				return State::Occupied;
			break;
		}
		case State::Occupied: {
			if (occupied >= 4)
				return State::Empty;
			break;
		}
		default: break;
	}

	return currentState;
}

auto apply_rules(const Layout& layout) -> Layout {
	Layout newLayout{layout};

	for (auto y = 0; y < layout.size(); y++) {
		for (auto x = 0; x < layout.front().size(); x++) {
			newLayout.at(y).at(x) = apply_rule(layout, {x, y});
		}
	}

	return newLayout;
}

auto day11(std::istream& stream) -> long {
	auto layout = parse_layout(stream);

	while (true) {
		const auto newLayout = apply_rules(layout);
		if (newLayout == layout)
			break;

		layout = std::move(newLayout);
	}

	return std::accumulate(layout.begin(), layout.end(), 0,
		[](auto sum, const auto& row) {
			return sum + std::count_if(row.begin(), row.end(),
				[](auto state) { return state == State::Occupied; });
			});
}
