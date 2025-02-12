#pragma once
#include <vector>
#include <string>
#include <map>
#include "Instruction.hpp"


struct VirtualFunction
{
	std::vector<Instruction*> instructionList;
};

class Program
{
	std::vector<VirtualFunction> vFunctionList;

public:

	void AddVirtualFunction(VirtualFunction vFunction)
	{
		vFunctionList.push_back(vFunction);
	}

	VirtualFunction GetVirtualFunction(int index) const
	{
		return vFunctionList[index];
	}

	void Print()
	{
		int i = 0;
		for (VirtualFunction vFunction : vFunctionList)
		{
			std::cout << "\nVFunction " << i << "\n";
			for (Instruction* instruction : vFunction.instructionList)
			{
				std::cout << "\t";
				instruction->Print();
			}
			i++;
		}
	}
};