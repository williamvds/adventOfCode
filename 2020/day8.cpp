#include <istream>
#include <map>
#include <sstream>
#include <vector>

enum class Opcode {
	None,
	Jump,
	Add,
};

struct Instruction {
	Opcode opcode;
	int operand;
	mutable bool executed = false;

	constexpr Instruction(Opcode opcode, int operand)
		: opcode{opcode}
		, operand{operand}
	{
	}
};

using Program = std::vector<Instruction>;

struct CPU {
	int accumulator = 0;
	size_t pc = 0;

	bool execute(const Instruction& instruction) {
		if (instruction.executed)
			return false;

		const int& operand = instruction.operand;

		switch (instruction.opcode) {
			case Opcode::None: break;
			case Opcode::Jump: pc += operand - 1; break;
			case Opcode::Add:  accumulator += operand; break;
		}

		instruction.executed = true;
		return true;
	}

	void run(const Program& program) {
		while (execute(program.at(pc))) {
			pc++;
		}
	}
};

const std::map<std::string_view, Opcode> mnemonics {
	{"nop", Opcode::None},
	{"jmp", Opcode::Jump},
	{"acc", Opcode::Add},
};

auto parse_mnemonic(std::string_view mnemonic) -> Opcode {
	return mnemonics.at(mnemonic);
}

auto parse_instruction(const std::string& line) -> Instruction {
	std::stringstream stream(line);
	std::string mnemonic;
	stream >> mnemonic;

	int operand;
	stream >> operand;

	return Instruction{parse_mnemonic(mnemonic), operand};
}

auto parse_program(std::istream& stream) -> Program {
	Program program;

	std::string line;
	while (std::getline(stream, line) && !line.empty())
		program.push_back(parse_instruction(line));

	return program;
}

int day8(std::istream& stream) {
	CPU cpu;
	const auto program = parse_program(stream);
	cpu.run(program);
	return cpu.accumulator;
}
