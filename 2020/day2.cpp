#include <istream>
#include <string_view>
#include <vector>

std::vector<size_t> find_indices(std::string_view string, char character)
{
	std::vector<size_t> indices;
	size_t index;
	while ((index = string.find(character)) != std::string_view::npos) {
		indices.push_back(index);
		string = string.substr(index + 1);
	}

	return indices;
}

auto validate(std::string_view string, char character, unsigned min, unsigned max)
	-> bool
{
	auto count = find_indices(string, character).size();
	return min <= count && count <= max;
}

int day2(std::istream& stream) {
	unsigned total = 0;

	while (!stream.eof())
	{
		int min, max;
		char character;
		std::string string;

		stream >> min;
		stream.ignore();
		stream >> max >> character;
		stream.ignore();
		stream >> string;

		if (validate(string, character, min, max))
			total++;
	}

	return total;
}
