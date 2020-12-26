#include <istream>
#include <optional>
#include <vector>

#include "shared.hpp"

constexpr auto historySize = 25;

template<class Iterator>
constexpr auto contains_paired_sum(Iterator begin, Iterator end, int sum) -> bool {
	const auto pairs = combination_pairs(begin, end);
	return std::any_of(pairs.begin(), pairs.end(), [&](const auto& pair) {
		return pair.first + pair.second == sum;
	});
}

int day9(std::istream& stream) {
	std::vector<int> history;

	int number;
	while (stream >> number) {
		if (history.size() >= historySize &&
			!contains_paired_sum(history.rbegin(), history.rbegin() + historySize, number))
			break;

		history.push_back(number);
	}

	return number;
}
