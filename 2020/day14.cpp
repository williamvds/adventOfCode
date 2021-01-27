#include <cstddef>
#include <istream>
#include <map>
#include <numeric>
#include <charconv>
#include <string_view>

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

class Computer {
public:
	constexpr void set_mask(std::string_view mask) { this->mask = mask; }
	constexpr void set_value(uint64_t address, uint64_t value) {
		memory.insert_or_assign(address, apply_mask(mask, value));
	}

	constexpr auto sum_memory() -> uint64_t {
		return std::accumulate(memory.cbegin(), memory.cend(), 0ul,
			[](const auto& left, const auto& right) {
				return left + right.second;
			});
	}

	void execute_command(std::string_view command) {
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
			set_value(address, value);
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
