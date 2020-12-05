#include <istream>
#include <vector>

int day1(std::istream& stream) {
	std::vector<int> entries;

	int entry;
	while (stream >> entry)
	{
		entries.push_back(entry);
	}

	for (auto first = entries.begin(); first < entries.end(); first++)
	{
		for (auto second = entries.begin(); second < entries.end(); second++)
		{
			if (first == second)
				continue;

			if (*first + *second == 2020)
				return (*first) * (*second);
		}
	}

	throw std::invalid_argument("No pairs sum to 2020");
}
