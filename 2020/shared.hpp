#include <functional>
#include <iterator>
#include <utility>
#include <vector>

template<class Iterator, class T = typename std::iterator_traits<Iterator>::value_type>
constexpr auto combination_pairs(Iterator begin, Iterator end) -> std::vector<std::pair<T, T>> {
	std::vector<std::pair<T, T>> results;

	for (auto first = begin; first < end; first++)
	{
		for (auto second = first + 1; second < end; second++)
		{
			results.push_back(std::make_pair(*first, *second));
		}
	}

	return results;
}

enum class RangeValidation {
	Valid,
	Invalid,
	Match,
};

template<
	class Iterator,
	class RangeValidator = std::function<RangeValidation(Iterator, Iterator)>
>
constexpr auto find_range(Iterator begin, Iterator end, RangeValidator validator)
	-> std::pair<Iterator, Iterator> {
	using R = RangeValidation;

	auto first = begin,
		 second = first + 1;
	for (; second != end; second++) {
		switch (validator(first, second)) {
			case R::Valid: continue;
			case R::Invalid:
				first++;
				second = first;
				break;
			case R::Match: return {first, second};
		}
	}

	return {first, second};
}
