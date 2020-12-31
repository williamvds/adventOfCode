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
	size_t previousNop = 0;
	size_t previousJump = 0;
	bool loopDetected = false;

	bool execute(const Instruction& instruction) {
		if (visitedInstructions.contains(pc)) {
			loopDetected = true;
			return false;
		}

		visitedInstructions.insert({pc, true});

		const int& operand = instruction.operand;

		switch (instruction.opcode) {
			case Opcode::None: previousNop = pc; break;
			case Opcode::Jump: jump(operand); break;
			case Opcode::Add:  accumulator += operand; break;
		}

		return true;
	}

	void run(const Program& program) {
		while (pc < program.size() && execute(program.at(pc))) {
			pc++;
		}
	}

	constexpr void jump(int offset) {
		previousJump = pc;
		pc += offset - 1;
	}

	constexpr void reset() {
		accumulator = 0;
		pc = 0;
		previousNop = 0;
		previousJump = 0;
		loopDetected = false;
		visitedInstructions.clear();
	}

private:
	std::map<size_t, bool> visitedInstructions;
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

auto day8(std::istream& stream) -> long {
	CPU cpu;
	const auto program = parse_program(stream);
	cpu.run(program);
	return cpu.accumulator;
}

auto day8Part2(std::istream& stream) -> long {
	CPU cpu;
	auto program = parse_program(stream);
	cpu.run(program);

	auto& previousJump = program.at(cpu.previousJump);
	auto& previousNop = program.at(cpu.previousNop);

	// Try swapping the last executed jump with a NOP
	previousJump.opcode = Opcode::None;
	cpu.reset();
	cpu.run(program);

	if (!cpu.loopDetected)
		return cpu.accumulator;

	// Try instead replacing the last executed NOP with a jump
	previousJump.opcode = Opcode::Jump;
	previousNop.opcode = Opcode::Jump;
	cpu.reset();
	cpu.run(program);

	return cpu.accumulator;
}
