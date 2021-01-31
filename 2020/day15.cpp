#include <algorithm>
#include <deque>
#include <istream>
#include <optional>

auto find_last_entry(const std::deque<unsigned>& queue, unsigned value)
-> std::optional<long> {
	const auto result = std::find(queue.crbegin() + 1, queue.crend(), value);
	if (result == queue.crend())
		return std::nullopt;
	return std::distance(queue.crbegin(), result);
}

auto next_spoken(const std::deque<unsigned>& queue) -> unsigned {
	if (const auto next = find_last_entry(queue, queue.back());
		next.has_value())
		return next.value();

	return 0;
}

auto parse_queue(std::istream& stream) -> std::deque<unsigned> {
	std::deque<unsigned> queue;

	unsigned number;
	while (stream >> number) {
		queue.push_back(number);
		if (stream.peek() == ',')
			stream.ignore();
	}

	return queue;
}

auto day15(std::istream& stream) -> long {
	auto queue = parse_queue(stream);

	while (queue.size() < 2020) {
		queue.push_back(next_spoken(queue));
	}

	return queue.back();
}
