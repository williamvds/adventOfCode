#include <algorithm>
#include <charconv>
#include <istream>
#include <string>
#include <vector>

auto parse_bus_lines(std::istream& stream) -> std::vector<int> {
	std::vector<int> lines;

	std::string entry;
	while (!stream.eof() && std::getline(stream, entry, ',')) {
		if (entry == "x") {
			continue;
		}

		const auto view = std::string_view{entry};
		int result;
		if (const auto [pointer, err] = std::from_chars(view.begin(), view.end(), result);
			err != std::errc())
			break;

		lines.push_back(result);
	}

	return lines;
}

auto day13(std::istream& stream) -> long {
	int timestamp;
	stream >> timestamp;
	stream.ignore(std::numeric_limits<std::streamsize>::max(), stream.widen('\n'));

	const auto lines = parse_bus_lines(stream);

	std::vector<int> delays;
	std::transform(lines.begin(), lines.end(), std::back_inserter(delays),
		[&](auto line) {
			int max = line;
			while (max < timestamp) {
				max += line;
			}
			return max - timestamp;
		});

	const auto result = std::min_element(delays.begin(), delays.end());
	if (result == delays.end())
		return 0;

	return *result * lines.at(std::distance(delays.begin(), result));
}
