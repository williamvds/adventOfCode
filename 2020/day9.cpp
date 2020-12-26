#include <functional>
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

template<
	class Iterator,
	class T = typename std::iterator_traits<Iterator>::value_type,
	class Validator = std::function<bool(Iterator, Iterator)>,
	class Comparator = std::function<bool(Iterator, Iterator)>
>
constexpr auto find_contiguous_range(Iterator begin, Iterator end, Validator isValid, Comparator isMatch)
	-> std::pair<Iterator, Iterator> {
	auto first = begin;
	for (auto second = first + 1; second != end; second++) {
		if (!isValid(first, second)) {
			first++;
			second = first;
			continue;
		}

		if (isMatch(first, second))
			return {first, second};
	}

	return {end, end};
}

int day9Part2(std::istream& stream) {
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

	auto [begin, end] = find_contiguous_range(history.begin(), history.end(),
		[&](auto begin, auto end) {
			return std::accumulate(begin, end, 0, std::plus<int>{}) <= invalidNumber.value();
		},
		[&](auto begin, auto end) {
			return std::accumulate(begin, end, 0, std::plus<int>{}) == invalidNumber.value();
		});

	return *std::min_element(begin, end) + *std::max_element(begin, end);
}
