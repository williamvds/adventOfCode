#include <istream>
#include <map>
#include <set>
#include <string>
#include <vector>

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

auto read_answer_group(std::istream& stream) -> std::vector<std::string> {
	std::vector<std::string> answers;

	std::string line;
	while (std::getline(stream, line)) {
		if (line.empty())
			break;

		answers.push_back(line);
	}

	return answers;
}

int day6Part2(std::istream& stream) {
	size_t total = 0;

	while (stream) {
		std::map<char, int> answerCounts;
		const auto answers = read_answer_group(stream);

		for (auto answer : answers) {
			const auto lineQuestions = get_questions(answer);
			for (auto question : lineQuestions) {
				answerCounts.try_emplace(question, 0);
				answerCounts.at(question)++;
			}
		}

		total += std::count_if(answerCounts.begin(), answerCounts.end(),
			[&](auto& pair){ return pair.second == answers.size(); });
	}

	return total;
}
