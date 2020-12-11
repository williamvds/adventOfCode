#include <algorithm>
#include <istream>
#include <iterator>
#include <tuple>
#include <vector>

template<class Iterator, class T = typename std::iterator_traits<Iterator>::value_type>
auto combination_pairs(Iterator begin, Iterator end) -> std::vector<std::pair<T, T>> {
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

template<class Iterator, class T = typename std::iterator_traits<Iterator>::value_type>
auto combination_triples(Iterator begin, Iterator end) -> std::vector<std::tuple<T, T, T>> {
	std::vector<std::tuple<T, T, T>> results;

	for (auto first = begin; first < end; first++)
	{
		for (auto second = first + 1; second < end; second++)
		{
			for (auto third = first; third < end; third++)
			{
				results.push_back(std::make_tuple(*first, *second, *third));
			}
		}
	}

	return results;
}

auto read(std::istream& stream) -> std::vector<int> {
	std::vector<int> entries;

	int entry;
	while (stream >> entry)
	{
		entries.push_back(entry);
	}

	return entries;
}

auto day1(std::istream& stream) -> int {
	auto entries = read(stream);
	auto pairs = combination_pairs(entries.begin(), entries.end());
	auto result = std::find_if(pairs.begin(), pairs.end(), [](auto pair) {
		return pair.first + pair.second == 2020;
	});

	if (result == pairs.end())
	{
		throw std::invalid_argument("No pairs sum to 2020");
	}

	return result->first * result->second;
}

auto day1Part2(std::istream& stream) -> int {
	auto entries = read(stream);
	auto triples = combination_triples(entries.begin(), entries.end());
	auto result = std::find_if(triples.begin(), triples.end(), [&](auto triple) {
		return std::apply([](auto... v) { return (v + ...); }, triple) == 2020;
	});

	if (result == triples.end())
	{
		throw std::invalid_argument("No triples sum to 2020");
	}

	return std::apply([](auto... v) { return (v * ...); }, *result);
}
