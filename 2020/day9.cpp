#include <istream>
#include <numeric>
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

auto day9(std::istream& stream) -> long {
	std::vector<int> history;

	long number;
	while (stream >> number) {
		if (history.size() >= historySize &&
			!contains_paired_sum(history.rbegin(), history.rbegin() + historySize, number))
			break;

		history.push_back(number);
	}

	return number;
}

auto day9Part2(std::istream& stream) -> long {
	std::vector<int> history;

	std::optional<int> invalidNumber;
	int number;
	while (stream >> number) {
		if (!invalidNumber.has_value() && history.size() >= historySize &&
			!contains_paired_sum(history.rbegin(), history.rbegin() + historySize, number)) {
			invalidNumber = number;
		}

		history.push_back(number);
	}

	auto [begin, end] = find_range(history.begin(), history.end(),
		[&](auto begin, auto end) {
			const auto sum = std::accumulate(begin, end, 0, std::plus<int>{});
			return sum == invalidNumber.value() ? RangeValidation::Match
				: sum < invalidNumber.value() ? RangeValidation::Valid
				: RangeValidation::Invalid;
		});

	return *std::min_element(begin, end) + *std::max_element(begin, end);
}
