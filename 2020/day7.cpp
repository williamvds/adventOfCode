#include <istream>
#include <map>
#include <regex>

using namespace std::literals::string_view_literals;

struct BagRule {
	std::string name;
	std::map<std::string, unsigned> contained;
};

using BagRules = std::map<std::string, BagRule>;

auto read_bag_rule(const std::string rule) -> BagRule {
	const auto subjectRegex = std::regex("(.+) bags contain (.*)");
	const auto containRegex = std::regex(R"((\d+) (.*?)(?: bags?[,.] ?)(.*))");
	BagRule result;

	std::smatch match;
	std::regex_match(rule, match, subjectRegex);
	result.name = match[1];

	auto remainder = match[2].str();

	while (std::regex_match(remainder, match, containRegex)) {
		const auto number = static_cast<unsigned>(std::stoul(match[1]));
		const auto name = match[2];
		result.contained.insert({name, number});
		remainder = match[3];
	}

	return result;
}

auto find_bag(const BagRules& rules, BagRule initialBag, std::string_view target)
	-> bool {
	if (initialBag.name == target)
		return true;

	return std::any_of(initialBag.contained.begin(), initialBag.contained.end(),
		[&](const auto& pair) {
			return find_bag(rules, rules.at(pair.first), target);
		});
}

int day7(std::istream& stream) {
	constexpr auto targetBag = "shiny gold";

	BagRules rules;
	std::string line;
	while (std::getline(stream, line)) {
		auto rule = read_bag_rule(line);
		rules.insert({rule.name, rule});
	}

	size_t total = 0;
	for (const auto& [name, rule] : rules) {
		if (name == targetBag)
			continue;

		if (find_bag(rules, rule, targetBag))
			total++;
	}

	return total;
}
