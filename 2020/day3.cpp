#include <istream>

constexpr char tree = '#';
constexpr unsigned movement = 3;

int day3(std::istream& stream) {
	std::string row;
	size_t column = 0, total = 0;

	while (stream >> row) {
		if (row[column] == tree)
			total++;

		column = (column + movement) % row.length();
	}

	return total;
}
