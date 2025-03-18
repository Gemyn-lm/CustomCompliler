#pragma once
#include <functional>

struct VariableSymbol
{
	int memoryAdress;
	// TODO : virtual type
	Compound_Statement* scope;

	VariableSymbol(int _memoryAdress, Compound_Statement* _scope)
		: memoryAdress(_memoryAdress), scope(_scope) { }
};

struct FunctionSymbol
{
	int functionIndex; // memory index


	// TODO : return type
	// TODO : arguments

	FunctionSymbol(int _functionIndex)
		: functionIndex(_functionIndex) { }
};

struct ExternalFunctionSymbol
{
	std::function<void(uint8_t* memory)> funcPtr;
	int functionIndex;

	ExternalFunctionSymbol(std::function<void(uint8_t* memory)> _funcPtr, int _index)
		: funcPtr(_funcPtr), functionIndex(_index) { }
};
