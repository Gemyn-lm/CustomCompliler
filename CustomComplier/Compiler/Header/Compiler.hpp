#pragma once
#include <string>
#include <vector>
#include <map>
#include "Program.hpp"
#include "Tokenizer.hpp"


struct Symbol
{
	int memoryAdress;
	// TODO : virtual type
	Compound_Statement* scope;

	Symbol(int _memoryAdress, Compound_Statement* _scope)
		: memoryAdress(_memoryAdress), scope(_scope) { }
};

class Compiler
{
public:

	Program Compile(const std::string& filename);

	void PrintDebugInfo();

	Symbol* TryGetSymbol(const std::string& symbolName)
	{
		auto it = variableSymbolMap.find(symbolName);
		return (it != variableSymbolMap.end()) ? &(it->second) : nullptr;
	}

	void AddInstruction(Instruction* instruction)
	{
		currentInstructionList.push_back(instruction);
	}

	int AddVariableSymbol(std::string& variableName, Compound_Statement* scope);
	void RemoveSymbolInScope(Compound_Statement* scope);
	std::vector<Instruction*> GetInstructions() const
	{
		return currentInstructionList;
	}

	size_t GetVarCountInScope(Compound_Statement* currentScope) const;

private:

	std::vector<Token*> tokenList;

	std::map<std::string, Symbol> variableSymbolMap;

	// instruction list for the current function
	std::vector<Instruction*> currentInstructionList;
};