#include <istream>
#include <set>
#include <string>

auto get_questions(std::string_view string) -> std::set<char> {
	return std::set<char>{string.begin(), string.end()};
}

int day6(std::istream& stream) {
	size_t total = 0;
	std::set<char> questions;

	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty()) {
			total += questions.size();
			questions.clear();
			continue;
		}

		const auto lineQuestions = get_questions(line);
		questions.insert(lineQuestions.begin(), lineQuestions.end());
	}

	return total;
}
