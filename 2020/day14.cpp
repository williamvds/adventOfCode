#include <charconv>
#include <cstddef>
#include <functional>
#include <istream>
#include <map>
#include <numeric>
#include <string_view>
#include <vector>

using namespace std::literals::string_view_literals;

constexpr auto maskCommandPrefix = "mask = "sv;
constexpr auto memoryCommandPrefix = "mem["sv;
constexpr auto memoryCommandSuffix = "] = "sv;

constexpr auto apply_mask(std::string_view mask, uint64_t value) -> uint64_t {
	for (auto i = 0; i < mask.length(); i++) {
		switch (mask[mask.length() - i - 1]) {
			case '0':
				value &= ~(1ul << i);
				break;
			case '1':
				value |= 1ul << i;
				break;
			default:
				break;
		}
	}

	return value;
}

static_assert(apply_mask("000000", 0b110011) == 0b000000);
static_assert(apply_mask("010100", 0b110011) == 0b010100);
static_assert(apply_mask("XXXXXX", 0b110010) == 0b110010);

template<class Container>
constexpr void apply_address_mask(
		char mask,
		unsigned index,
		uint64_t value,
		std::insert_iterator<Container> inserter) {
	switch (mask) {
		case '0':
			inserter = value;
			break;
		case '1':
			inserter = value | 1ul << index;
			break;
		default:
			inserter = value & ~(1ul << index);
			inserter = value | 1ul << index;
			break;
	}
}

class Computer {
public:
	using Processor = void(Computer::*)(uint64_t address, uint64_t value);

	constexpr void set_mask(std::string_view mask) { this->mask = mask; }
	constexpr void set_masked_value(uint64_t address, uint64_t value) {
		memory.insert_or_assign(address, apply_mask(mask, value));
	}

	constexpr auto sum_memory() -> uint64_t {
		return std::accumulate(memory.cbegin(), memory.cend(), 0ul,
			[](const auto& left, const auto& right) {
				return left + right.second;
			});
	}

	auto set_masked_address(uint64_t address, uint64_t value) {
		std::vector<uint64_t> addresses { address };

		for (auto index = 0; index < mask.length(); index++) {
			std::vector<uint64_t> newAddresses;

			for (auto address : addresses) {
				apply_address_mask(
					mask.at(mask.length() - index - 1), index, address,
					std::inserter(newAddresses, newAddresses.end()));
			}

			addresses = std::move(newAddresses);
		}

		for (auto address : addresses) {
			memory.insert_or_assign(address, value);
		}
	}

	void execute_command(
			std::string_view command,
			Processor processor = &Computer::set_masked_value) {
		if (command.starts_with(maskCommandPrefix))
			set_mask(command.substr(maskCommandPrefix.length()));
		else if (command.starts_with(memoryCommandPrefix)) {
			const auto suffix = command.find(memoryCommandSuffix);

			const auto addressString = command.substr(
				memoryCommandPrefix.length(),
				suffix);
			uint64_t address;
			std::from_chars(addressString.data(),
					addressString.data() + addressString.length(),
					address);

			const auto valueString = command.substr(
				suffix + memoryCommandSuffix.length());
			uint64_t value;
			std::from_chars(valueString.data(),
					valueString.data() + valueString.length(),
					value);
			std::invoke(processor, this, address, value);
		}
	}

private:
	std::string mask;
	std::map<uint64_t, uint64_t> memory;
};

auto day14(std::istream& stream) -> long {
	Computer computer;

	std::string command;
	while (std::getline(stream, command)) {
		computer.execute_command(command);
	}

	return computer.sum_memory();
}

auto day14Part2(std::istream& stream) -> long {
	Computer computer;

	std::string command;
	while (std::getline(stream, command)) {
		computer.execute_command(command, &Computer::set_masked_address);
	}

	return computer.sum_memory();
}
