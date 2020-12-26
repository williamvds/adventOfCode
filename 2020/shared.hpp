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
