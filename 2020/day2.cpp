#include <functional>
#include <istream>
#include <string_view>
#include <vector>

auto find_indices(std::string_view string, char character) -> std::vector<size_t>
{
	std::vector<size_t> indices;
	size_t index = 0;
	while ((index = string.find(character, index)) != std::string_view::npos) {
		indices.push_back(index);
		index++;
	}

	return indices;
}

auto validate(std::string_view string, char character, unsigned min, unsigned max)
	-> bool
{
	auto count = find_indices(string, character).size();
	return min <= count && count <= max;
}

template<typename T>
auto find(const std::vector<T>& vector, T value) -> bool {
	return std::find(vector.begin(), vector.end(), value) != vector.end();
}

auto validate2(std::string_view string, char character, unsigned index1, unsigned index2)
	-> bool
{
	auto indices = find_indices(string, character);
	return find(indices, static_cast<size_t>(index1 - 1)) != find(indices, static_cast<size_t>(index2 - 1));
}

using Validator = std::function<bool(std::string_view, char, unsigned, unsigned)>;
auto process(std::istream& stream, Validator validator) -> size_t {
	size_t total = 0;

	while (!stream.eof())
	{
		int number1, number2;
		char character;
		std::string string;

		stream >> number1;
		stream.ignore();
		stream >> number2 >> character;
		stream.ignore();
		stream >> string;

		if (validator(string, character, number1, number2))
			total++;
	}

	return total;
}

auto day2(std::istream& stream) -> long {
	return process(stream, validate);
}

auto day2Part2(std::istream& stream) -> long {
	return process(stream, validate2);
}
