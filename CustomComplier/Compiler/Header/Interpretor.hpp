#pragma once
#include "VirtualMemory.hpp"
#include "Instruction.hpp"
#include "Program.hpp"
#include <vector>

class Interpretor
{
private:

	VirtualMemory virtualMemory;
	Program program;

public:

	Interpretor(Program _program, size_t memorySize)
		: program(_program), virtualMemory(VirtualMemory(memorySize, program.GetExternalFunctionListPtr()))
	{
	}

	void Run(int functionIndex = 0, bool printInfo = false);
	void PrintStack(size_t count);
};