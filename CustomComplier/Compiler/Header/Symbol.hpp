#pragma once

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