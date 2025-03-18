#pragma once
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Instruction.hpp"


struct VirtualFunction
{
	std::vector<Instruction*> instructionList;
};

class Program
{
	std::vector<VirtualFunction> vFunctionList;
	std::vector<std::function<void(uint8_t* memory)>> externalFunctionList;

public:

	void AddVirtualFunction(VirtualFunction vFunction)
	{
		vFunctionList.push_back(vFunction);
	}

	void AddExternalFunction(std::function<void(uint8_t* memory)> vFunction)
	{
		externalFunctionList.push_back(vFunction);
	}

	std::vector<std::function<void(uint8_t* memory)>>* GetExternalFunctionListPtr()
	{
		return &externalFunctionList;
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