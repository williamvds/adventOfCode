#include <cmath>
#include <functional>
#include <istream>
#include <numeric>
#include <vector>

#include "shared.hpp"

const auto maxDifference = 3;

auto parse_adapters(std::istream& stream) -> std::vector<int> {
	std::vector<int> ratings { 0 };

	int rating;
	while (stream >> rating) {
		ratings.push_back(rating);
	}

	std::sort(ratings.begin(), ratings.end());
	ratings.push_back(*ratings.rbegin() + maxDifference);

	return ratings;
}

auto day10(std::istream& stream) -> long {
	auto ratings = parse_adapters(stream);

	std::adjacent_difference(ratings.begin(), ratings.end(), ratings.begin(),
		[](auto left, auto right) {
			return std::abs(left - right);
		});

	return std::count_if(ratings.begin(), ratings.end(), [](auto difference) {
			return difference == 1;
		})
		* std::count_if(ratings.begin(), ratings.end(), [](auto difference) {
			return difference == 3;
		});
}

auto day10Part2(std::istream& stream) -> long {
	auto ratings = parse_adapters(stream);

	std::adjacent_difference(ratings.begin(), ratings.end(), ratings.begin(),
		[](auto left, auto right) {
			return std::abs(left - right);
		});

	long combinations = 1;

	size_t total = 0;
	std::pair range{ratings.begin() + 1, ratings.begin() + 1};
	while (range.second != ratings.end()) {
		const auto difference = *range.second;
		total += difference;

		if (total > maxDifference) {
			const auto count = std::distance(range.first, range.second - 1);
			combinations *= std::pow(2, count);
			range.first++;
			range.second = range.first + 1;
			total = difference;
		}

		range.second++;
	}

	return combinations;
}
