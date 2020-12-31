#include <istream>
#include <map>
#include <numeric>
#include <regex>

using namespace std::literals::string_view_literals;

constexpr auto targetBag = "shiny gold";

struct BagRule {
	std::string name;
	std::map<std::string, unsigned> contained;
};

using BagRules = std::map<std::string, BagRule>;

auto parse_bag_rule(const std::string rule) -> BagRule {
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

auto parse_bag_rules(std::istream& stream) -> BagRules {
	BagRules rules;

	std::string line;
	while (std::getline(stream, line)) {
		auto rule = parse_bag_rule(line);
		rules.insert({rule.name, rule});
	}

	return rules;
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

auto day7(std::istream& stream) -> long {
	const auto rules = parse_bag_rules(stream);

	size_t total = 0;
	for (const auto& [name, rule] : rules) {
		if (name == targetBag)
			continue;

		if (find_bag(rules, rule, targetBag))
			total++;
	}

	return total;
}

auto count_bags(const BagRules& rules, BagRule initialBag) -> size_t {
	return std::accumulate(initialBag.contained.begin(), initialBag.contained.end(),
		0, [&](auto sum, const auto& pair) {
			return sum + pair.second + pair.second * count_bags(rules, rules.at(pair.first));
		});
}

auto day7Part2(std::istream& stream) -> long {
	const auto rules = parse_bag_rules(stream);
	return count_bags(rules, rules.at(targetBag));
}
