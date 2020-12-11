#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string_view>

#include <fmt/core.h>
#include <argagg.hpp>

#include "main.hpp"

auto argparser = argagg::parser{{
	{"help", {"-h", "--help"}, "shows this help message", 0},
	{"day", {"-d", "--day"}, "day to execute", 1},
	{"input", {"-i", "--input"}, "input file", 0},
}};

constexpr auto usage = "Advent of Code 2020\n"
	"Usage: {} [options] [input file...]\n";

void run(std::string day, const std::string& path) {
	if (path == "-") {
		std::cerr << "Running day " << day << " on standard input\n";
		days.at(day)(std::cin);
	} else {
		std::cerr << "Running day " << day << " on " << path << '\n';
		auto file = std::ifstream{path};
		std::cout << days.at(day)(file) << '\n';
	}
}

void output_days(std::ostream& stream) {
	stream << "Available days: \n";
	for (auto pair : days) {
		stream << pair.first << '\n';
	}
}

int main(int argc, char **argv)
{
	argagg::parser_results args;
	try {
		args = argparser.parse(argc, argv);
	} catch (const std::exception& ex) {
		argagg::fmt_ostream help(std::cerr);
		help << usage << argparser << '\n'
			<< "Encountered exception while parsing arguments: " << ex.what()
			<< '\n';
	}

	if (args["help"] || args.count() < 1) {
		argagg::fmt_ostream help(std::cerr);
		help << fmt::format(usage, argv[0]) << argparser;
	}

	auto day = args["day"].as<std::string>();
	if (!days.contains(day)) {
		std::cerr << fmt::format("Specified day {0} unavailable.\n", day);
		output_days(std::cerr);
		return EXIT_FAILURE;
	}

	if (args["input"]) {
		run(day, args["input"].as<std::string>());
	}

	for (auto arg : args.pos) {
		run(day, arg);
	}

	return EXIT_SUCCESS;
}
