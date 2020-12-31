#include <numeric>
#include <istream>
#include <vector>

auto day10(std::istream& stream) -> long {
	std::vector<int> ratings { 0 };

	int rating;
	while (stream >> rating) {
		ratings.push_back(rating);
	}

	std::sort(ratings.begin(), ratings.end());
	ratings.push_back(*ratings.rbegin() + 3);

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
