#include <array>
#include <functional>
#include <istream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

using StringMap = std::unordered_map<std::string, std::string>;
using Validator = std::function<bool(const std::string& string)>;

constexpr char keyDelimiter = ':';
constexpr auto digits = "0123456789";
constexpr auto hexDigits = "0123456789abcdef";
constexpr auto eyeColors = std::to_array({
	"amb",
	"blu",
	"brn",
	"gry",
	"grn",
	"hzl",
	"oth",
});
constexpr auto centimeterSuffix = "cm";
constexpr auto inchSuffix = "in";

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

auto string_to_int(const std::string& string, int& result) -> bool {
	try {
		result = std::stoi(string);
		return true;
	} catch (const std::invalid_argument&) {
		return false;
	}
}

std::unordered_map<std::string, Validator> validators {
	{"byr", [](auto value) {
		int num;
		return string_to_int(value, num) && 1920 <= num && num <= 2002;
	}},
	{"iyr", [](auto value) {
		int num;
		return string_to_int(value, num) && 2010 <= num && num <= 2020;
	}},
	{"eyr", [](auto value) {
		int num;
		return string_to_int(value, num) && 2020 <= num && num <= 2030;
	}},
	{"hgt", [](auto value) {
		if (int num;
			value.ends_with(centimeterSuffix) &&
			string_to_int(value.substr(0, value.length() - 2), num) &&
			150 <= num && num <= 193) {
			return true;
		}

		if (int num;
			value.ends_with(inchSuffix) &&
			string_to_int(value.substr(0, value.length() - 2), num) &&
			59 <= num && num <= 76) {
			return true;
		}

		return false;
	}},
	{"hcl", [](auto value) {
		return value.length() == 7 &&
			 value[0] == '#' &&
			 value.find_last_not_of(hexDigits) == 0;
	}},
	{"ecl", [](auto value) {
		return std::any_of(eyeColors.begin(), eyeColors.end(),
			[&](auto color) { return color == value; });
	}},
	{"pid", [](auto value) {
		return value.length() == 9 &&
			value.find_first_not_of(digits) == std::string::npos;
	}},
};

auto passport_values_valid(const StringMap& map) -> bool {
	for (const auto& [key, value] : map) {
		if (validators.contains(key) && !validators[key](value))
			return false;
	}
	return true;
}

int day4Part2(std::istream& stream) {
	size_t total = 0;

	StringMap map = read_entry(stream);
	while (!map.empty()) {
		if (passport_valid(map) && passport_values_valid(map))
			total++;

		map = read_entry(stream);
	}

	return total;
}
