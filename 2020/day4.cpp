#include <array>
#include <istream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

using StringMap = std::unordered_map<std::string, std::string>;

constexpr char keyDelimiter = ':';

auto parse_map(std::stringstream& stream)
-> StringMap {
	StringMap map;

	std::string word;
	while (stream >> word) {
		const auto index = word.find(keyDelimiter);

		if (index == std::string::npos)
			return map;

		map.insert({word.substr(0, index), word.substr(index + 1)});
	}

	return map;
}

auto passport_valid(const StringMap& map) -> bool {
	constexpr auto keys = std::to_array({
		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid",
	});

	return std::all_of(keys.begin(), keys.end(),
		[&map](auto& key) { return map.contains(key); });
}

auto read_entry(std::istream& stream) -> StringMap {
	std::stringstream stringStream;
	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty())
			break;

		stringStream << line << ' ';
	}

	return parse_map(stringStream);
}

int day4(std::istream& stream) {
	size_t total = 0;

	StringMap map = read_entry(stream);
	while (!map.empty()) {
		if (passport_valid(map))
			total++;

		map = read_entry(stream);
	}

	return total;
}
