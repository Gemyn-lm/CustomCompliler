#include "Interpretor.hpp"



void Interpretor::Run(int functionIndex, bool printInfo)
{
	virtualMemory.currentFunctionIndex = functionIndex;
	while (virtualMemory.currentInstructionIndex < program.GetVirtualFunction(virtualMemory.currentFunctionIndex).instructionList.size())
	{
		if (printInfo)
		{
			std::cout << "\n\n";
			program.GetVirtualFunction(virtualMemory.currentFunctionIndex).instructionList[virtualMemory.currentInstructionIndex]->Print();
		}
		
		program.GetVirtualFunction(virtualMemory.currentFunctionIndex).instructionList[virtualMemory.currentInstructionIndex]->Execute(&virtualMemory);
		virtualMemory.currentInstructionIndex++;

		if(printInfo)
			PrintStack(7);
	}
}

void Interpretor::PrintStack(size_t count)
{
	std::cout << "\nSTACK :\n\n";
	std::cout << "\033[33m";
	for (int i = 0; i < count; i++)
	{
		if (i * 4 >= virtualMemory.GetStackHead())
			std::cout << "\033[37m";
		std::cout << "[" << i * 4 << "]" << " " << virtualMemory.ReadMemory(-virtualMemory.GetStackHead() + i * 4) << "\n";
	}
}
